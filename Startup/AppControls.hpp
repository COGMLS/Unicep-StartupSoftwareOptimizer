/** @file AppControls.hpp
 * 
 * @short Provide all functions to control the console app
*/

#pragma once

#ifndef APP_CONTROLS_HPP
#define APP_CONTROLS_HPP

#include <iostream>
#include <thread>
#include <vector>
#include "CustomMessages.hpp"
#include "AppDataStruct.hpp"
#include "Loader.hpp"

int makeThreads(std::vector<std::thread*>& threadsV, unsigned int useNThreads);
int prepareThread(std::thread* thread, initApp const& app);
int prepareThread(std::thread* thread, initProtocol const& protocol);

#endif // !APP_CONTROLS_HPP