#pragma once

#ifndef APPDATASTRUCT_HPP
#define APPDATASTRUCT_HPP

#include <string>
#include <chrono>
#include <filesystem>

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
		long delay;
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
		long long time2Open;
	public:
		initApp(std::string showName, std::filesystem::path basePath, std::string execName, std::string args, Priority_t priority, long delay);
		~initApp();
		long long getTime2Open();
		std::filesystem::path getBasePath();
		std::string getExecName();
		std::string getArgs();
};

class initProtocol: public initData
{
	private:
		std::string protocolName;
		long long time2Open;
	public:
		initProtocol(std::string showName, std::string protocolName, Priority_t priority, long delay);
		~initProtocol();
		std::string getProtocolName();
		long long getTime2Open();
};

#endif // !APPDATASTRUCT_HPP