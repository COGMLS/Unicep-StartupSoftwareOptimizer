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

short chkLangValue(int& argc, const char* argv)
{
	int i = isValidTokenElement(argc, argv, "--lang");

	i++;

	if (i < argc)
	{

	}
}