#pragma once

#ifndef AUXLIB_HPP
#define AUXLIB_HPP

#include <cstdlib>
#include <string>

int getEnv(std::string& envPath, const char* varName);

#endif // !AUXLIB_HPP