#include "Loader.hpp"

Profile::Profile(std::filesystem::path profileCfgFile)
{
	// Set the default profile working path
	this->profilePath = profileCfgFile.parent_path();

	// Open the base profile config file
	std::fstream profileConfig(profileCfgFile, std::ios::in);
	std::string temp;

	// Check and load the profile base config
	int i = 0;
	while (std::getline(profileConfig, temp))
	{
		if (i == 1)
		{
			this->name = temp;
			temp.clear();
		}

		if (i == 2)
		{
			this->description = temp;
			temp.clear();
		}

		i++;
	}

	// Close profile config file
	profileConfig.close();

	// Get the local current time
	std::time_t time = std::time(nullptr);
	this->calendarData = std::gmtime(&time);

	// Convert the wday to string and use it to define the final path
	std::filesystem::path p1 = "\\" + std::to_string(this->calendarData->tm_wday);
	std::filesystem::path p2 = this->profilePath;
	p2 += p1;

	// Initialyze the priority queues
	this->appQueue = new std::priority_queue<initApp>;
	this->protocolQueue = new std::priority_queue<initProtocol>;

	// Get recursively the directories and files
	std::filesystem::recursive_directory_iterator startCfgs(p2);

	// Create temporary pointer for receave the apps and protocols initialyzation data
	initApp* appTemp = nullptr;
	initProtocol* protocolTemp = nullptr;

	// For each item inside current folder, load the correct file and send for proper function
	for (const std::filesystem::directory_entry& dirEntry : startCfgs)
	{
		if (dirEntry.is_regular_file())
		{
			// Check for app init file
			if (dirEntry.path().extension() == ".app")
			{
				appTemp = loadAppConfig(dirEntry.path());

				if (appTemp != nullptr)
				{
					this->appQueue->push(*appTemp);
					appTemp = nullptr;
				}
			}

			// Check for protocol init file
			if (dirEntry.path().extension() == ".protocol")
			{
				protocolTemp = loadProtocolConfig(dirEntry.path());

				if (protocolTemp != nullptr)
				{
					this->protocolQueue->push(*protocolTemp);
					protocolTemp = nullptr;
				}
			}
		}
	}

	delete appTemp;
	delete protocolTemp;

	appTemp = nullptr;
	protocolTemp = nullptr;
}

Profile::~Profile()
{
	delete this->calendarData;
	delete this->appQueue;
	delete this->protocolQueue;

	this->calendarData = nullptr;
	this->appQueue = nullptr;
	this->protocolQueue = nullptr;
}

std::string Profile::getName()
{
	return this->name;
}

std::string Profile::getDescription()
{
	return this->description;
}

initApp const& Profile::getApp()
{
	// TODO: insert return statement here
	return this->appQueue->top();
}

initProtocol const& Profile::getProtocol()
{
	// TODO: insert return statement here
	return this->protocolQueue->top();
}

void Profile::add2Queue(initApp app)
{
	this->appQueue->push(app);
}

void Profile::add2Queue(initProtocol protocol)
{
	this->protocolQueue->push(protocol);
}

size_t Profile::appQueueSize()
{
	return this->appQueue->size();
}

size_t Profile::protocolQueueSize()
{
	return this->protocolQueue->size();
}

initApp* loadAppConfig(std::filesystem::path initDataCfgFile)
{
	initApp* initTemp = nullptr;

	int errAcq = 0;
	int errAcqTimeHistory = 0;

	try
	{
		std::fstream config(initDataCfgFile, std::ios::in);

		std::string buffer;

		// Secondary buffers
		std::string name = "";
		Priority_t priority;
		long delay = 0;
		std::filesystem::path* basePath = nullptr;
		std::string execName = "";
		std::string args = "";
		std::vector<long long> time2OpenHistory;

		int i = 0;
		while (std::getline(config, buffer))
		{
			// Show name
			if (i == 1)
			{
				if (isCfgToken(buffer, "NAME"))
				{
					name = buffer;
				}
				else
				{
					errAcq += 2 ^ i;
				}
			}

			// Priority
			if (i == 2)
			{
				if (isCfgToken(buffer, "PRIORITY"))
				{
					if (std::strcmp(buffer.c_str(), "LOW") == 0)
					{
						priority = Priority_t::LOW;
					}
					else if (std::strcmp(buffer.c_str(), "NORMAL") == 0)
					{
						priority = Priority_t::NORMAL;
					}
					else if (std::strcmp(buffer.c_str(), "HIGH") == 0)
					{
						priority = Priority_t::HIGH;
					}
					else
					{
						priority = Priority_t::NORMAL;
					}
				}
				else
				{
					errAcq += 2 ^ i;
				}
			}

			// Delay
			if (i == 3)
			{
				if (isCfgToken(buffer, "DELAY"))
				{
					try
					{
						delay = std::stol(buffer);
					}
					catch (const std::exception&)
					{
						delay = 0;
					}
				}
				else
				{
					errAcq += 2 ^ i;
				}
			}

			// App base path
			if (i == 4)
			{
				if (isCfgToken(buffer, "PATH"))
				{
					basePath = new std::filesystem::path(buffer);
				}
				else
				{
					errAcq += 2 ^ i;
				}
			}

			// App executable
			if (i == 5)
			{
				if (isCfgToken(buffer, "EXE"))
				{
					execName = buffer;
				}
				else
				{
					errAcq += 2 ^ i;
				}
			}

			// App args
			if (i == 6)
			{
				if (isCfgToken(buffer, "ARGS"))
				{
					args = buffer;
				}
				else
				{
					errAcq += 2 ^ i;
				}
			}

			// Time to open
			if (i == 7)
			{
				if (isCfgToken(buffer, "TIME_HISTORY"))
				{
					getTimeHistory(buffer, time2OpenHistory, errAcqTimeHistory);
				}
				else
				{
					errAcq += 2 ^ i;
				}
			}
		}

		config.close();

		if (errAcq > 0 && errAcqTimeHistory > 0)
		{
			return nullptr;
		}

		initTemp = new initApp(name, *basePath, execName, args, priority, delay, time2OpenHistory);

		return initTemp;
	}
	catch (const std::exception& e)
	{
		return nullptr;
	}
}

initProtocol* loadProtocolConfig(std::filesystem::path initDataCfgFile)
{
	initProtocol* initTemp = nullptr;

	int errAcq = 0;
	int errAcqHIstory = 0;

	try
	{
		std::fstream config(initDataCfgFile, std::ios::in);

		std::string buffer;

		// Secondary buffers
		std::string name = "";
		std::string protocolName = "";
		Priority_t priority;
		long delay = 0;
		std::vector<long long> time2OpenHistory;

		int i = 0;

		while (std::getline(config, buffer))
		{
			// Show name
			if (i == 1)
			{
				if (isCfgToken(buffer, "NAME"))
				{
					name = buffer;
				}
				else
				{
					errAcq += 2 ^ i;
				}
			}

			// Priority
			if (i == 2)
			{
				if (isCfgToken(buffer, "PRIORITY"))
				{
					if (std::strcmp(buffer.c_str(), "LOW") == 0)
					{
						priority = Priority_t::LOW;
					}
					else if (std::strcmp(buffer.c_str(), "NORMAL") == 0)
					{
						priority = Priority_t::NORMAL;
					}
					else if (std::strcmp(buffer.c_str(), "HIGH") == 0)
					{
						priority = Priority_t::HIGH;
					}
					else
					{
						priority = Priority_t::NORMAL;
					}
				}
				else
				{
					errAcq += 2 ^ i;
				}
			}

			// Delay
			if (i == 3)
			{
				if (isCfgToken(buffer, "DELAY"))
				{
					try
					{
						delay = std::stol(buffer);
					}
					catch (const std::exception&)
					{
						delay = 0;
					}
				}
				else
				{
					errAcq += 2 ^ i;
				}
			}

			// Protocol name

			i++;
		}

		if (errAcq > 0 || errAcqHIstory > 0)
		{
			return nullptr;
		}

		config.close();

		initTemp = new initProtocol(name, protocolName, priority, delay, time2OpenHistory);

		return initTemp;
	}
	catch (const std::exception&)
	{
		return nullptr;
	}
}

bool isCfgToken(std::string& configStr, const char* configToken)
{
	std::string temp = configStr;

	char* token = const_cast<char*>(configToken);

	std::strcpy(token, "=");

	if (temp._Starts_with(configToken))
	{
		temp.replace(0, std::strlen(token), "");

		configStr = temp;

		return true;
	}

	return false;
}

void getTimeHistory(std::string& strData, std::vector<long long>& timeHistory, int& errAcq)
{
	std::string buffer;

	int i = 0;
	while (i < strData.size())
	{
		if (strData[i] != ',' || strData[i] != '\0')
		{
			buffer += strData[i];
		}
		else
		{
			try
			{
				long long convertedBuffer = std::stoll(buffer);
				timeHistory.push_back(convertedBuffer);
			}
			catch (const std::exception&)
			{
				errAcq++;
			}

			buffer.clear();
		}

		i++;
	}
}