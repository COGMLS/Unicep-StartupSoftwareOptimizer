/**
* @file CmdLine.hpp
* @short This library provides the functions to make the command line analisis.
* @author Matheus L. Silvati
* @version 0.0.1a
*/

#pragma once

#ifndef CMDLINE_HPP
#define CMDLINE_HPP

	#include <cstring>
	#include <string>
	#include <cctype>

	#define MAXCMDLINEOPTIONS 2

	enum class CmdLineOptionsIndex
	{
		lang = 0,
		loadpath = 1
	};

	const char* CmdLineOptions[MAXCMDLINEOPTIONS] =
	{
		"--lang",
		"--loadpath"
	};

	const char* langCmdLineOptions[2] =
	{
		"en",	// English
		"pt"	// Portuguese
	};

	int isValidTokenElement(int &argc, const char* argv[], const char* tokenTest);
	int isValidTokenElement(int &argc, const char* argv[], const char* tokenTest, int pos);

	/// <summary>
	/// Convert any possible non lower char on token to be tested to ignore the case sensitive
	/// </summary>
	/// <param name="tokenTest">Token to test and convert</param>
	/// <returns>Return an const char* converted token to lower strings</returns>
	const char* tokenToLower(const char* tokenTest);

	short chkLangValue(int& argc, const char* argv[]);
	bool chkLoadPathValue(int& argc, const char* argv[], std::string& outLoadPath);

#endif // !CMDLINE_HPP