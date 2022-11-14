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

int readConfig(std::fstream& fs, const char* token, std::string& config)
{
	if (fs.is_open())
	{
		if (fs.is_open())
		{
			if (fs.tellg() != 0)
			{
				fs.clear();
				fs.seekg(0, std::ios::beg);
			}

			std::string temp, temp2;
			while (std::getline(fs, temp))
			{
				for (int j = 0; j < temp.size(); j++)
				{
					temp2 += temp[j];

					if (std::strcmp(token, temp2.c_str()) == 0)
					{
						temp.replace(0, std::strlen(token), "");
						config = temp;
						return 0;		// Configuration founded and exported
					}
				}

				temp2.clear();
			}
		}

		return 2;	// Configuration not founded
	}

	return 1;		// Config file not available
}

int chkFile(std::filesystem::path path, std::filesystem::path filePath)
{
	if (chkItem(path, filePath))
	{
		return 0;	// File exist
	}
	else
	{
		std::fstream fs;
		fs.open(filePath, std::ios::out);
		fs.close();

		if (chkItem(path, filePath))
		{
			return 1;	// File created
		}
		else
		{
			return -1;	// Fail to create the file
		}
	}
}

bool chkItem(std::filesystem::path path, std::filesystem::path item)
{
	std::filesystem::recursive_directory_iterator r(path);
	std::filesystem::directory_entry d(item);
	for (const std::filesystem::directory_entry& entry : r)
	{
		if (entry == d)
		{
			return true;
		}
	}
	return false;
}
