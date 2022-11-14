#pragma once

#ifndef AUXLIB_HPP
#define AUXLIB_HPP

#include <cstdlib>
#include <string>
#include <fstream>
#include <filesystem>

int getEnv(std::string& envPath, const char* varName);
int readConfig(std::fstream& fs, const char* token, std::string& config);
int chkFile(std::filesystem::path path, std::filesystem::path filePath);
bool chkItem(std::filesystem::path path, std::filesystem::path item);

#endif // !AUXLIB_HPP