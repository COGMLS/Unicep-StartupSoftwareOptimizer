#pragma once

#ifndef LOADER_HPP
#define LOADER_HPP

#include <ctime>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include "AppDataStruct.hpp"

class Profile
{
	private:
		std::string name;
		std::string description;
		std::tm* calendarData = nullptr;
		std::filesystem::path profilePath;
		//std::filesystem::recursive_directory_iterator* internalConfigs = nullptr;
		std::priority_queue<initApp>* appQueue = nullptr;
		std::priority_queue<initProtocol>* protocolQueue = nullptr;
	public:
		Profile(std::filesystem::path profileCfgFile);
		~Profile();
		std::string getName();
		std::string getDescription();
		initApp const& getApp();
		initProtocol const& getProtocol();
		void add2Queue(initApp app);
		void add2Queue(initProtocol protocol);
		size_t appQueueSize();
		size_t protocolQueueSize();
};

//std::filesystem::recursive_directory_iterator internalConfigDirs(std::filesystem::path basePath);
//int loadConfig(std::filesystem::path configBasePath, std::time_t currentTime, std::priority_queue<initApp> &appQueue, std::priority_queue<initProtocol> &protocolQueue);
initApp* loadAppConfig(std::filesystem::path initDataCfgFile);
initProtocol* loadProtocolConfig(std::filesystem::path initDataCfgFile);


#endif // !LOADER_HPP