/**
* @file LoaderLib.hpp
* @short This library provides the functions to load the applications
* @author Matheus L. Silvati
* @version 0.0.1a
*/

#pragma once

#ifndef LOADERLIB_HPP
#define LOADERLIB_HPP

	#include <iostream>
	#include <string>
	#include <thread>
	#include <chrono>

	// Base to all initialyzation types
	class appLoadBase
	{
		protected:
			std::string basePath;
			int initStatus;
		public:
			int getStatus();
			std::string getBasePath();
			virtual void start();
	};

	// Class for applications initiation
	class appInit: public appLoadBase
	{
		private:
			std::string appPath;
			std::string appName;
		public:
			void start();
	};

	// Class for protocol based apps start
	class protocolInit: public appLoadBase
	{
		private:
			std::string protocolName;
		public:
			void start();
	};

	bool isBasePathAvailable(std::string& loadPath);
	bool isConfigFileAvailable(std::string& loadPath);

#endif // !LOADERLIB_HPP