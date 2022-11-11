#pragma once

#ifndef APPDATASTRUCT_HPP
#define APPDATASTRUCT_HPP

#include <string>
#include <vector>
#include <chrono>
#include <filesystem>

extern const std::string BASE_APPDATA_DIR;

enum Priority_t
{
	LOW,
	NORMAL,
	HIGH
}
typedef Priority_t;

class initData
{
	protected:
		std::string showName;
		Priority_t priority;
		std::chrono::high_resolution_clock::duration delay;
		std::chrono::high_resolution_clock::time_point start, end;
	public:
		initData();
		~initData();
		std::string getShowName();
		Priority_t getPriority();
		long getDelay();
};

class initApp: public initData
{
	private:
		std::filesystem::path basePath;
		std::string execName;
		std::string args;
		std::chrono::high_resolution_clock::time_point time2Open;
		std::vector<long long>time2OpenHistory;
	public:
		initApp(std::string showName, std::filesystem::path basePath, std::string execName, std::string args, Priority_t priority, long delay, std::vector<long long>time2OpenHistory);
		~initApp();
		long long getTime2Open();
		std::filesystem::path getBasePath();
		std::string getExecName();
		std::string getArgs();
		virtual void startup();
};

class initProtocol: public initData
{
	private:
		std::string protocolName;
		std::chrono::high_resolution_clock::time_point time2Open;
		std::vector<long long>time2OpenHistory;
	public:
		initProtocol(std::string showName, std::string protocolName, Priority_t priority, long delay, std::vector<long long>time2OpenHistory);
		~initProtocol();
		std::string getProtocolName();
		long long getTime2Open();
		virtual void startup();
};

#endif // !APPDATASTRUCT_HPP