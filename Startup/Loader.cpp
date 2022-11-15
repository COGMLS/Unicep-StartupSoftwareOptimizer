#include "Loader.hpp"

Profile::Profile(std::filesystem::path profileCfgFile)
{
	// Set the default profile working path
	this->profilePath = profileCfgFile.parent_path();

	// Open the base profile config file
	std::fstream profileConfig(profileCfgFile, std::ios::in);
	std::string temp;

	// Check and load the profile base config
	if (readConfig(profileConfig, "PROFILE_NAME=", temp) == 0)
	{
		this->name = temp;
		temp.clear();
	}
	else
	{
		this->name = "FAIL TO LOAD PROFILE_NAME";
	}

	if (readConfig(profileConfig, "PROFILE_DESCRIPTION=", temp) == 0)
	{
		this->description = temp;
		temp.clear();
	}
	else
	{
		this->description = "FAIL TO LOAD PROFILE_DESCRIPTION";
	}

	// Close profile config file
	profileConfig.close();

	// Get the local current time
	std::time_t time = std::time(nullptr);
	this->calendarData = std::gmtime(&time);

	// Convert the wday to string and use it to define the final path
	std::filesystem::path p1 = this->profilePath.generic_string() + "\\" + std::to_string(this->calendarData->tm_wday);

	// Initialyze the priority queues
	this->appQueue = new std::priority_queue<initApp>;
	this->protocolQueue = new std::priority_queue<initProtocol>;

	// Get recursively the directories and files
	std::filesystem::recursive_directory_iterator startCfgs(p1);

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
	return this->appQueue->top();
}

initProtocol const& Profile::getProtocol()
{
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

		// Show name
		if (readConfig(config, "NAME=", buffer) == 0)
		{
			name = buffer;
		}
		else
		{
			errAcq += 2 ^ 0;
		}

		// Priority
		if (readConfig(config, "PRIORITY=", buffer) == 0)
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
			errAcq += 2 ^ 1;
		}

		// Delay
		if (readConfig(config, "DELAY=", buffer) == 0)
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
			errAcq += 2 ^ 2;
		}

		// App base path
		if (readConfig(config, "PATH=", buffer) == 0)
		{
			basePath = new std::filesystem::path(buffer);
		}
		else
		{
			errAcq += 2 ^ 3;
		}

		// App executable
		if (readConfig(config, "EXE=", buffer) == 0)
		{
			execName = buffer;
		}
		else
		{
			errAcq += 2 ^ 4;
		}

		// App args
		if (readConfig(config, "ARGS=", buffer) == 0)
		{
			args = buffer;
		}
		else
		{
			errAcq += 2 ^ 5;
		}

		// Time to open
		if (readConfig(config, "TIME_HISTORY=", buffer) == 0)
		{
			getTimeHistory(buffer, time2OpenHistory, errAcqTimeHistory);
		}
		else
		{
			errAcq += 2 ^ 6;
		}

		config.close();

		if (errAcq > 0 && errAcqTimeHistory > 0)
		{
			return nullptr;
		}

		initTemp = new initApp(name, *basePath, execName, args, priority, delay, time2OpenHistory);

		return initTemp;
	}
	catch (const std::exception&)
	{
		return nullptr;
	}
}

initProtocol* loadProtocolConfig(std::filesystem::path initDataCfgFile)
{
	initProtocol* initTemp = nullptr;

	int errAcq = 0;
	int errAcqTimeHistory = 0;

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

		// Show name
		if (readConfig(config, "NAME=", buffer) == 0)
		{
			name = buffer;
		}
		else
		{
			errAcq += 2 ^ 0;
		}

		// Priority
		if (readConfig(config, "PRIORITY=", buffer) == 0)
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
			errAcq += 2 ^ 1;
		}

		// Delay
		if (readConfig(config, "DELAY=", buffer) == 0)
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
			errAcq += 2 ^ 2;
		}

		// Protocol name
		if (readConfig(config, "PROTOCOL=", buffer) == 0)
		{
			protocolName = buffer;
		}
		else
		{
			errAcq += 2 ^ 3;
		}

		// Time to open
		if (readConfig(config, "TIME_HISTORY=", buffer) == 0)
		{
			getTimeHistory(buffer, time2OpenHistory, errAcqTimeHistory);
		}
		else
		{
			errAcq += 2 ^ 4;
		}

		config.close();

		if (errAcq > 0 || errAcqTimeHistory > 0)
		{
			return nullptr;
		}

		initTemp = new initProtocol(name, protocolName, priority, delay, time2OpenHistory);

		return initTemp;
	}
	catch (const std::exception&)
	{
		return nullptr;
	}
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

int chkProfile(std::string& loadProfile, std::filesystem::path& profileCfgPath)
{
	std::string appDataPath;

	if (getEnv(appDataPath, "AppData") == 0)
	{
		try
		{
			std::filesystem::path loadProfilePath(appDataPath + "\\" + BASE_APPDATA_DIR);

			// Check for base appdata configs folder
			if (std::filesystem::exists(loadProfilePath))
			{
				loadProfilePath += "\\" + loadProfile;

				// If the profile folder exist
				if (std::filesystem::exists(loadProfilePath))
				{
					std::filesystem::path profileConfigFile = loadProfilePath.generic_string() + "\\profile.cfg";
			
					// Check if the profile config file exist
					if (std::filesystem::exists(profileConfigFile))
					{
						std::fstream fs;

						fs.open(profileConfigFile, std::ios::in);

						// Try to reach the file
						if (fs.is_open())
						{
							fs.close();

							profileCfgPath = profileConfigFile;

							return 0;	// Configuration file can be opened
						}
				
						return 6;	// Configuration file can't be opened
					}

					return 5;	// Fail to get the profile configuration file
				}

				return 4;	// Fail to get the profile folder
			}

			return 3;	// Fail to check the base appdata configs
		}
		catch (const std::exception&)
		{
			return 2;	// Catch return
		}
	}

	return 1;	// Fail to get the environment variable
}

void Profile::remAppQueue()
{
	this->appQueue->pop();
}

void Profile::remProtocolQueue()
{
	this->protocolQueue->pop();
}