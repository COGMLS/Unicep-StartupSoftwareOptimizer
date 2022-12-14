#include "CmdLine.hpp"

int isValidTokenElement(int &argc, const char* argv[], const char* tokenTest)
{
	for (int i = 0; i < argc; i++)
	{
		if (std::strcmp(tokenTest, tokenToLower(argv[i])) == 0)
		{
			return i;	// Return the argv token element index
		}
	}

	return -1;			// The token isn't available for the command line
}

int isValidTokenElement(int& argc, const char* argv[], const char* tokenTest, int pos)
{
	if (pos < argc)
	{
		for (int i = pos; i < argc; i++)
		{
			if (std::strcmp(tokenTest, tokenToLower(argv[i])) == 0)
			{
				return i;	// Return the argv token element index
			}
		}

		return -1;			// The token isn't available for the command line
	}

	return -2;				// The start position was incorrect
}

const char* tokenToLower(const char* tokenTest)
{
	const size_t tknlen = std::strlen(tokenTest);

	char* newTokenTest = new char[tknlen];

	for (size_t i = 0; i < tknlen; i++)
	{
		if (std::islower(tokenTest[i]) == 0)
		{
			newTokenTest[i] = std::tolower(tokenTest[i]);
		}
		else
		{
			newTokenTest[i] = tokenTest[i];
		}
	}

	return const_cast<const char*>(newTokenTest);
}

short chkLangValue(int& argc, const char* argv[])
{
	int langTokenIndex = isValidTokenElement(argc, argv, "--lang");

	if (langTokenIndex >= 0 && langTokenIndex + 1 < argc)
	{
		const char* langType = argv[langTokenIndex++];

		if (std::strcmp("en", tokenToLower(langType)) == 0)
		{
			return 0;	// Define the program to english
		}
		else if (std::strcmp("pt", tokenToLower(langType)) == 0)
		{
			return 1;	// Define the program to portuguese
		}
		else
		{
			return -1;	// Language argument sended but no config was defined
		}
	}
	else
	{
		return -2;		// Language token sended to command line, using the default value.
	}
}

bool chkLoadPathValue(int& argc, const char* argv[], std::string& outLoadPath)
{
	int loadPathTokenIndex = isValidTokenElement(argc, argv, "--loadpath");

	if (loadPathTokenIndex >= 0 && loadPathTokenIndex + 1 < argc)
	{
		outLoadPath = argv[loadPathTokenIndex++];

		return true;	// An possible value for load path was founded, but not tested.
	}

	return false;		// --loadpath was sended to command line arguments, but there is no argument for this parameter
}