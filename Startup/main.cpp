/** Unicep - Startup Software Optimizer project
* ---------------------------------------------------------
* About this program:
* -------------------
* The Startup program is used to make the software startup
* with argumments and diagnostics about the initialization
* and export the log about the task.
* ----------------------------------------------------------
* Configurations:
* ---------------
* 
* 
* 
*/

// ISO C++ Headers:
#include <iostream>
#include <locale>

// Windows Headers:

// Custom Headers:
#include "CmdLine.hpp"
#include "CustomMessages.hpp"
#include "Loader.hpp"


int main(int argc, const char* argv[])
{
    short lang = chkLangValue(argc, argv);

    if (lang == 0 || lang == -2)
    {
        // Try to set the english language on UTF-8 console.
        try
        {
            std::locale appLang("en_US.utf8", std::locale::all);
            std::locale::global(appLang);
        }
        catch (const std::exception& e)
        {
            // Use colorized strings on console with ASCII encoding:
            std::cout << msg::writeError("Fail to set the app location.") << std::endl;

            std::cerr << msg::writeError(e.what()) << '\n';

            std::cout << "\nPress Enter to continue...";
            #pragma warning (suppress : 6031)
            std::getchar();

            return 1;   // Set location fail.
        }
    }
    else if (lang == 1)
    {
        // Try to set the portuguese language on UTF-8 console.
        try
        {
            std::locale appLang("pt_BR", std::locale::all);
            std::locale::global(appLang);
        }
        catch (const std::exception& e)
        {
            // Use colorized strings on console with ASCII encoding:
            std::cout << msg::writeError("Fail to set the app location.") << std::endl;

            std::cerr << msg::writeError(e.what()) << '\n';

            std::cout << "\nPress Enter to continue...";
            #pragma warning (suppress : 6031)
            std::getchar();

            return 1;   // Set location fail.
        }
    }
    else
    {
        return 2;   // Fail to define the program language!
    }

    msg::showPresentation("Startup Software Optimizer");

    std::string loadPath;

    if (chkLoadPathValue(argc, argv, loadPath)) // Change function to get the profile name directly
    {
        // Test loadPath
    }

    return 0;
}