/**
 * @short Custom Messages Library
 * @author Matheus L. Silvati
 * @version 0.4.15
*/

#pragma once

#ifndef CUSTOM_MSG_HPP
#define CUSTOM_MSG_HPP

#include <iostream>

// Namespace for ASCII formated message functions
namespace msg
{
    // App presentation
    void showPresentation(std::string title);

    // Write a string information message
    std::string writeInfo(std::string infoMsg, bool useBrightColor = false);

    // Write a string success message
    std::string writeSuccess(std::string successMsg, bool useBrightColor = false);

    // Write a string warning message
    std::string writeWarning(std::string warnMsg, bool useBrightColor = false);

    // Write a string error message
    std::string writeError(std::string errMsg, bool useBrightColor = false);

    // Write a debug string message
    std::string writeDebugMsg(std::string dbgMsg, bool useBrightColor = false);
} // namespace msg

#endif // !CUSTOM_MSG_HPP