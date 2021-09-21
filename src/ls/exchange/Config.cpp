#include "ls/exchange/Config.h"
#include "ls/DefaultLogger.h"

using namespace std;

namespace ls
{
	namespace exchange
	{
		exchange::Config::Config()
		{
			load();
		}

		string Config::getConfigPath()
		{
			char *configPath = getenv("LS_EXCHANGE_CONFIG_PATH");
			if(nullptr == configPath)
				configPath = (char *)"config.json";
			return configPath;
		}

		void Config::init()
		{
			json::api.get(root, "apiKey", apiKey);
			json::api.get(root, "secretKey", secretKey);
			json::api.get(root, "ip", ip);
			json::api.get(root, "apiURL", apiURL);
			json::api.get(root, "buyText", buyText);
			json::api.get(root, "sellText", sellText);
			json::api.get(root, "coin", coin);
			json::api.get(root, "number", number);
			json::api.get(root, "rate", rate);
			json::api.get(root, "uprate", uprate);

			LOGGER(ls::INFO) << "apiKey: " << "****" << ls::endl;
			LOGGER(ls::INFO) << "secretKey: " << "****" << ls::endl;
			LOGGER(ls::INFO) << "ip: " << ip << ls::endl;
			LOGGER(ls::INFO) << "apiURL: " << apiURL << ls::endl;
			LOGGER(ls::INFO) << "buyText: " << buyText << ls::endl;
			LOGGER(ls::INFO) << "sellText: " << sellText << ls::endl;
			LOGGER(ls::INFO) << "coin: " << coin << ls::endl;
			LOGGER(ls::INFO) << "number: " << number << ls::endl;
			LOGGER(ls::INFO) << "rate: " << rate << ls::endl;
			LOGGER(ls::INFO) << "uprate: " << uprate << ls::endl;
		}
	}
}
