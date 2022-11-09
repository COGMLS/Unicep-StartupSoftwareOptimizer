#include "AppDataStruct.hpp"

initData::initData()
{
	this->showName = "Default string";
	this->priority = Priority_t::NORMAL;
	this->delay = 0;
}

initData::~initData()
{
	// Do nothing
}

std::string initData::getShowName()
{
	return this->showName;
}

Priority_t initData::getPriority()
{
	return this->priority;
}

long initData::getDelay()
{
	return this->delay;
}

initApp::initApp(std::string showName, std::filesystem::path basePath, std::string execName, std::string args, Priority_t priority, long delay)
{
	this->showName = showName;
	this->basePath = basePath;
	this->execName = execName;
	this->args = args;
	this->priority = priority;
	this->delay = delay;
}

initApp::~initApp()
{
	// Do nothing
}

long long initApp::getTime2Open()
{
	return this->time2Open;
}

std::filesystem::path initApp::getBasePath()
{
	return this->basePath;
}

std::string initApp::getExecName()
{
	return this->execName;
}

std::string initApp::getArgs()
{
	return this->args;
}

initProtocol::initProtocol(std::string showName, std::string protocolName, Priority_t priority, long delay)
{
	this->showName = showName;
	this->protocolName = protocolName;
	this->priority = priority;
	this->delay = delay;
}

initProtocol::~initProtocol()
{
	// Do nothing
}

std::string initProtocol::getProtocolName()
{
	return this->protocolName;
}

long long initProtocol::getTime2Open()
{
	return this->time2Open;
}
