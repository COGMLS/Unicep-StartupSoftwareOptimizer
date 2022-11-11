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

	try
	{
		std::fstream config(initDataCfgFile, std::ios::in);

		std::string temp;

		int i = 0;
		while (std::getline(config, temp))
		{
			// Show name
			if (i == 1)
			{

			}

			// Priority
			if (i == 2)
			{

			}

			// Delay
			if (i == 3)
			{

			}

			// App base path
			if (i == 4)
			{

			}

			// App executable
			if (i == 5)
			{

			}

			// App args
			if (i == 6)
			{

			}

			// Time to open
			if (i == 7)
			{

			}
		}

		return initTemp;
	}
	catch (const std::exception& e)
	{
		return nullptr;
	}
}
