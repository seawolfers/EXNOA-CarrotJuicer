﻿#include "config.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#define CJCONFIG_READ_PROPERTY(field, j, c) if (j.contains(#field)) c.field = j.at(#field)

using json = nlohmann::json;

namespace config
{
	config_struct config = {
		true, true, false, "", 100
	};

	void load()
	{
		if (!std::filesystem::exists("cjconfig.json"))
		{
			return;
		}

		try
		{
			nlohmann::json j;
			std::ifstream i("cjconfig.json");
			i >> j;

			CJCONFIG_READ_PROPERTY(save_request, j, config);
			CJCONFIG_READ_PROPERTY(save_response, j, config);
			CJCONFIG_READ_PROPERTY(enable_notifier, j, config);
			CJCONFIG_READ_PROPERTY(notifier_host, j, config);
			CJCONFIG_READ_PROPERTY(notifier_connection_timeout_msec, j, config);

			std::cout << "Loaded cjconfig.json\n";
		}
		catch (const std::exception& e)
		{
			std::cout << "Exception reading cjconfig.json: " << e.what() << "\n";
		}
	}

	const config_struct& get()
	{
		return config;
	}
}