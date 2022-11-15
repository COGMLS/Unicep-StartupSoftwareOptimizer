#include "AppDataStruct.hpp"

const std::string BASE_APPDATA_DIR = "StartupOptimizer";

initData::initData()
{
	this->showName = "Default string";
	this->priority = Priority_t::NORMAL;
	this->delay = std::chrono::high_resolution_clock::duration(0);
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
	return static_cast<long>(this->delay.count());
}

initApp::initApp(std::string showName, std::filesystem::path basePath, std::string execName, std::string args, Priority_t priority, long delay, std::vector<long long> time2OpenHistory)
{
	this->showName = showName;
	this->basePath = basePath;
	this->execName = execName;
	this->args = args;
	this->priority = priority;
	this->delay = std::chrono::high_resolution_clock::duration(delay);
	this->time2OpenHistory = time2OpenHistory;
}

initApp::~initApp()
{
	// Do nothing
}

long long initApp::getTime2Open()
{
	return (this->end - this->start).count();
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

void initApp::startup()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	ZeroMemory(&pi, sizeof(pi));

	std::string cmdLine = this->basePath.generic_string() + "\\" + this->execName + " " + this->args;
	std::wstring wcmdLine(cmdLine.begin(), cmdLine.end());	// Convert to use on Windows API

	LPWSTR lpws = wcmdLine.data();

	if (this->delay.count() > 0)
	{
		std::this_thread::sleep_for(this->delay);
	}

	// Register the start time
	this->start = std::chrono::high_resolution_clock::now();

	// Try to create the process
	if (!CreateProcess(
			NULL,	// No module, will use the commmand line
			lpws,	// Using the wcmdLine
			NULL,	// process handle
			NULL,	// thread handle
			FALSE,	// Set handle inheritance to FALSE
			0,		// No creation flags
			NULL,	// Use parent's environment block
			NULL,	// Use parent's starting directory
			&si,	// Access si struct
			&pi		// Access pi struct
		)
	)
	{
		DWORD wait = WaitForInputIdle(pi.hProcess, GLOBAL_WAITINPUTIDLE);

		// Register the stop time
		this->end = std::chrono::high_resolution_clock::now();

		// If wait equal zero, the WaitForInpuIdle was ended with success
		if (wait == 0)
		{
			this->time2Open = (this->end - this->start).count();

			// If time2OpenHistory is equal than MAX_TIME2OPENHISTORY_ENTRIES, replace by the first one (older value)
			if (this->time2OpenHistory.size() == MAX_TIME2OPENHISTORY_ENTRIES)
			{
				long long* temp = nullptr;

				for (int i = 0; i < (this->time2OpenHistory.size() - 1); i++)
				{
					if (i + 1 < this->time2OpenHistory.size())
					{
						temp = &this->time2OpenHistory[i + 1];
						this->time2OpenHistory[i] = *temp;
						temp = nullptr;
					}
				}
			}
			else
			{
				this->time2OpenHistory.push_back(this->time2Open);
			}
		}
		else if (wait == WAIT_TIMEOUT)
		{

		}
		else
		{

		}
	}
	else
	{

	}
}

initProtocol::initProtocol(std::string showName, std::string protocolName, Priority_t priority, long delay, std::vector<long long> time2OpenHistory)
{
	this->showName = showName;
	this->protocolName = protocolName;
	this->priority = priority;
	this->delay = std::chrono::high_resolution_clock::duration(delay);
	this->time2OpenHistory = time2OpenHistory;
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
	return (this->end - this->start).count();
}

void initProtocol::startup()
{

}
