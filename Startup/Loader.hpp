#pragma once

#ifndef LOADER_HPP
#define LOADER_HPP

#include <ctime>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include "AppDataStruct.hpp"
#include "AuxLib.hpp"

class Profile
{
	private:
		std::string name;
		std::string description;
		std::tm* calendarData = nullptr;
		std::filesystem::path profilePath;
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
		void remAppQueue();
		void remProtocolQueue();
		size_t appQueueSize();
		size_t protocolQueueSize();
};

initApp* loadAppConfig(std::filesystem::path initDataCfgFile);
initProtocol* loadProtocolConfig(std::filesystem::path initDataCfgFile);
void getTimeHistory(std::string& strData, std::vector<long long>& timeHistory, int& errAcq);
int chkProfile(std::string& loadProfile, std::filesystem::path& profileCfgPath);

#endif // !LOADER_HPP