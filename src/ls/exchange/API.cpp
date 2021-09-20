#include "ls/exchange/API.h"
#include "ls/http/Request.h"
#include "ls/http/Response.h"
#include "ls/ssl/Client.h"
#include "ls/ssl/Connection.h"
#include "ls/net/Client.h"
#include "ls/cstring/API.h"
#include "ls/Exception.h"
#include "ls/DefaultLogger.h"
#include "ls/SHA256.h"
#include "unistd.h"
#include "time.h"
#include "memory"

using namespace std;

namespace ls
{
	namespace exchange
	{
		double round2(double value)
		{
			int v = value * 100;
			return v / 100.0;
		}

		API::API() : in(nullptr, new Buffer()), out(nullptr, new Buffer())
		{
			
		}

		void API::buy(const string &coin, double price, double number)
		{
			order(coin, price, number, config.buyText);
		}

		void API::sell(const string &coin, double price, double number)
		{
			order(coin, price, number, config.sellText);
		}

		void API::run()
		{
			for(;;)
			{
				sleep(2);
				auto prices = getPrices(config.coin);
				auto buyOrderNumber = getBuyOrderNumberAndMax(config.coin);
				if(buyOrderNumber.first == 0)
				{
					sell(config.coin, prices[0], config.number);
					buy(config.coin, round2(prices[0] * (1 - config.rate)), config.number);
				}
				else
				{
					if(buyOrderNumber.first >= 5)
						continue;
					long long currentPrice = (long long)(prices[0] * 10000);
					long long signPriceNow = (long long)(buyOrderNumber.second * (1 + config.uprate) * 10000);
					if(currentPrice > signPriceNow)
					{
						sell(config.coin, prices[0], config.number);
						buy(config.coin, round2(prices[0] * (1 - config.rate)), config.number);
					}
				}
			}
		}

		string API::transacation(const string &method, const string &url, const string &body, const map<string, string> &attributes)
		{
			http::Request request;
			request.setDefaultHeader();
			request.getMethod() = method;
			request.getURL() = url;
			request.getBody() = body;
			request.getVersion() = "HTTP/1.1";
			request.setAttribute("Host", config.apiURL);
			request.setAttribute("User-Agent", "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:89.0) Gecko/20100101 Firefox/89.0");
			if(body != "")
				request.setAttribute("Content-Length", to_string(body.size()));
			for(auto &attribute : attributes)
				request.setAttribute(attribute.first, attribute.second);
			ssl::Client sslClient;
			unique_ptr<ssl::Connection> connection(sslClient.getConnection(net::Client(config.ip, 443).connect()));
			connection -> setHostname(url);
			connection -> connect();
			
			out.reset(connection -> getWriter());
			string text = request.toString();
			
			LOGGER(ls::INFO) << "request:\n" << text << ls::endl;
			
			out.append(text);
			out.write();

			LOGGER(ls::INFO) << "cmd sending..." << ls::endl;

			in.reset(connection -> getReader());

			http::Response response;
			string result;
			for(;;)
			{
				in.read();
				LOGGER(ls::INFO) << "reading..." << ls::endl;
				try
				{
					if(response.getCode() == "")
					{
						auto text = in.split("\r\n\r\n", true);
						response.parseFrom(text);
					}
					int contentLength = stoi(response.getAttribute("Content-Length"));
					result = in.split(contentLength);
				}
				catch(Exception &e)
				{
					sleep(1);
					continue;
				}
				break;
			}
			return result;
		}

		std::string API::signature(const vector<string> &v)
		{
			int los;
			for(auto &i : v)
				los += i.size();
			string signaturePayload(los, '\0');
			char *text = (char *)signaturePayload.c_str();
			for(auto &i : v)
				text = cstring::api.append(text, i.c_str());
			ls::SHA256 sha256;
			return sha256.hmac(signaturePayload, config.secretKey);				
		}	
	}
}
