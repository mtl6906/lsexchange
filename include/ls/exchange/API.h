#ifndef LS_EXCHANGE_API_H
#define LS_EXCHANGE_API_H

#include "ls/exchange/Config.h"
#include "ls/io/InputStream.h"
#include "ls/io/OutputStream.h"
#include "map"
#include "vector"
#include "string"

namespace ls
{
	namespace exchange
	{
		class API
		{
			public:
				API();
				void run();
				void buy(const std::string &coin, double price, double number);	
				void sell(const std::string &coin, double price, double number);
				virtual std::vector<double> getPrices(const std::string &coin) = 0;
				virtual std::pair<int, double> getBuyOrderNumberAndMax(const std::string &coin) = 0;
			protected:
				std::string signature(const std::vector<std::string> &v);
				virtual std::string order(const std::string &coin, double price, double number, const std::string &side) = 0;
				std::string transacation(const std::string &method, const std::string &path, const std::string &body = "", const std::map<std::string, std::string> &attribute = std::map<std::string, std::string>());
				exchange::Config config;
				io::InputStream in;
				io::OutputStream out;
		};
	}
}

#endif
