#include "AppControls.hpp"

int makeThreads(std::vector<std::thread*>& threadsV, unsigned int useNThreads)
{
	unsigned int maxThreadsSupported = std::thread::hardware_concurrency();
	
	// If useNThreads was equal to 0, the useNThreads will be setted to 50% of maxThreadsSupported
	// If maxThreadsSupported was bigger than 1
	if (maxThreadsSupported >= useNThreads || useNThreads == 0)
	{
		if (useNThreads == 0)
		{
			if (maxThreadsSupported == 1)
			{
				useNThreads = 1;
			}
			else
			{
				useNThreads = maxThreadsSupported / 2;
			}
		}

		if (threadsV.size() == 0)
		{
			try
			{
				for (int i = 0; i < useNThreads; i++)
				{
					std::thread* pT = nullptr;
					threadsV.push_back(pT);
				}

				return 0;	// threadsV was define with success
			}
			catch (const std::exception&)
			{
				return 3;	// Catch fail
			}
		}

		return 2;	// The threads vector already defined
	}

	return 1;	// Configuration fail
}

int prepareThread(std::thread* thread, initApp const& app)
{
	try
	{
		if (thread == nullptr)
		{
			thread = new std::thread(&initApp::startup, app);

			if (thread->joinable())
			{
				thread->join();

				thread->~thread();

				thread = nullptr;

				return 0;	// Executed with success
			}
			else
			{
				thread->~thread();
				thread = nullptr;

				return 3;	// Fail to join
			}
		}
		else
		{
			return 2;	// This thread is in use
		}
	}
	catch (const std::exception&)
	{
		return 1;		// Catch fail
	}
}

int prepareThread(std::thread* thread, initProtocol const& protocol)
{
	try
	{
		if (thread == nullptr)
		{
			thread = new std::thread(&initProtocol::startup, protocol);

			if (thread->joinable())
			{
				thread->join();

				thread->~thread();

				thread = nullptr;

				return 0;	// Executed with success
			}
			else
			{
				thread->~thread();
				thread = nullptr;

				return 3;	// Fail to join
			}
		}
		else
		{
			return 2;	// This thread is in use
		}
	}
	catch (const std::exception&)
	{
		return 1;		// Catch fail
	}
}