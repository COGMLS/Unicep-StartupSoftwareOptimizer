#include "AuxLib.hpp"

int getEnv(std::string& envPath, const char* varName)
{
	char* envBuffer = nullptr;
	size_t envBufferSize;

	// Try to get the buffer size
	getenv_s(&envBufferSize, NULL, 0, "AppData");

	if (envBufferSize == 0)
	{
		return 1;	// The environment variable doesn't exist!
	}
	else
	{
		envBuffer = (char*) std::malloc(envBufferSize * sizeof(char));

		if (!envBuffer)
		{
			return 2;	// Fail to allocate memory
		}
		else
		{
			// Get the environment variable:
			getenv_s(&envBufferSize, envBuffer, envBufferSize, "AppData");

			envPath = envBuffer;	// Export the value to std::string

			std::free(envBuffer);

			envBuffer = nullptr;

		}
	}
	
	return 0;	// The environment variable was founded and exported with success!
}
