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


int main(int argc, const char* argv[])
{
    // Try to set the portuguese language on UTF-8 console.
    // Check the notes about the possibilities.
    try
    {
        // Set the application language to pt-BR on UTF-8 encoding.
        //std::locale appLang("pt_BR", std::locale::all);
        //std::locale::global(appLang);

        //gcc bug: it fails if try to compile in pt_BR.uft8, but not in en_US.utf8
        std::locale::global(std::locale("en_US.utf8"));

        
    }
    catch (const std::exception& e)
    {
        // Use colorized strings on console with ASCII encoding:
        std::cout << msg::writeError("Fail to set the app location.") << std::endl;

        std::cerr << msg::writeError(e.what()) << '\n';

        std::cout << "\nPress Enter to continue...";
        std::getchar();

        return 1;   // Set location fail.
    }
    return 0;
}