#ifndef LS_EXCHANGE_CONFIG_H
#define LS_EXCHANGE_CONFIG_H

#include "ls/Config.h"
#include "string"

namespace ls
{
	namespace exchange
	{
		class Config : public ls::Config
		{
			public:
				std::string apiKey;
				std::string secretKey;
				std::string ip;
				std::string apiURL;
				std::string buyText;
				std::string sellText;
				std::string coin;
				double number;
				double rate;
				double uprate;
				Config();
				std::string getConfigPath() override;
				void init() override;
		};
	}
}

#endif
