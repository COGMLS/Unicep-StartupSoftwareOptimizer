/**
 * @short Definition of functions on cmsg.hpp file
 * @author Matheus L. Silvati
*/

#include "CustomMessages.hpp"

// Namespace for ASCII formated message functions
namespace msg
{
    // App presentation
    void showPresentation(std::string title)
    {
        std::cout << "\033[96m" << title << "\033[0m" << std::endl;
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "UNICEP - P.I.M. 8\n";
        std::cout << "\nAlunos:\n Matheus L. Silvati | RA: 4200872\nCaroline Paganelli Corrêa dos Santos | RA: 4200890\n";
        std::cout << "---------------------------------------\n" << std::endl;
    }

    // Write a string information message
    std::string writeInfo(std::string infoMsg, bool useBrightColor)
    {
        std::string temp;
        if (useBrightColor)
        {
            temp = "[\033[94mINFO\033[0m]";
        }
        else
        {
            temp = "[\033[34mINFO\033[0m]";
        }
        temp += "::"; // Separator
        temp += infoMsg;
        return temp;
    }

    // Write a string success message
    std::string writeSuccess(std::string successMsg, bool useBrightColor)
    {
        std::string temp;
        if (useBrightColor)
        {
            temp = "[\033[92mSUCCESS\033[0m]";
        }
        else
        {
            temp = "[\033[32mSUCCESS\033[0m]";
        }
        temp += "::"; // Separator
        temp += successMsg;
        return temp;
    }

    // Write a string warning message
    std::string writeWarning(std::string warnMsg, bool useBrightColor)
    {
        std::string temp;
        if (useBrightColor)
        {
            temp = "[\033[93mWARNING\033[0m]";
        }
        else
        {
            temp = "[\033[33mWARNING\033[0m]";
        }
        temp += "::"; // Separator
        temp += warnMsg;
        return temp;
    }

    // Write a string error message
    std::string writeError(std::string errMsg, bool useBrightColor)
    {
        std::string temp;
        if (useBrightColor)
        {
            temp = "[\033[91mERROR\033[0m]";
        }
        else
        {
            temp = "[\033[31mERROR\033[0m]";
        }
        temp += "::"; // Separator
        temp += errMsg;
        return temp;
    }

    // Write a debug string message
    std::string writeDebugMsg(std::string dbgMsg, bool useBrightColor)
    {
        std::string temp;
        if (useBrightColor)
        {
            temp = "[\033[95mDEBUG\033[0m]";
        }
        else
        {
            temp = "[\033[35mDEBUG\033[0m]";
        }
        temp += "::"; // Separator
        temp += dbgMsg;
        return temp;
    }
} // namespace msg