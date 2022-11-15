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
#include <filesystem>

// Windows Headers:

// Custom Headers:
#include "CmdLine.hpp"
#include "CustomMessages.hpp"
#include "Loader.hpp"
#include "AppControls.hpp"

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

    std::string profileName;

    if (chkLoadProfile(argc, argv, profileName)) // Change function to get the profile name directly
    {
        // Test profile
        std::filesystem::path profilePath;

        int chkProfileStatus = chkProfile(profileName, profilePath);
        if (chkProfileStatus == 0)
        {
            std::cout << msg::writeInfo("Loading profile " + profileName + "...") << std::endl;

            Profile* profile = nullptr;

            try
            {
                profile = new Profile(profilePath);
                std::vector<std::thread*> threadsV;
                unsigned int maxThreads = 2;

                std::cout << msg::writeSuccess("Profile " + profile->getName() + " loaded!") << std::endl;
                std::cout << msg::writeInfo("Loading " + std::to_string(profile->protocolQueueSize() + profile->appQueueSize()) + " applications...") << std::endl;

                makeThreads(threadsV, maxThreads);

                // Create the threads for create the process
                if (threadsV.size() > 0)
                {
                    int i = 0;
                    bool initA = true;
                    int errAcq = 0;
                    while (profile->protocolQueueSize() + profile->appQueueSize() > 0)
                    {
                        if (errAcq > 0)
                        {
                            return 6;   // Error founded
                        }

                        if (i > maxThreads)
                        {
                            i = 0;      // Recycle the threadV index
                        }
                        
                        if (initA)
                        {
                            int thrResult = prepareThread(threadsV[i], profile->getApp());

                            if (thrResult == 0)
                            {
                                profile->remAppQueue();
                            }
                            else if (thrResult != 2 && thrResult != 0)
                            {
                                profile->remAppQueue();
                            }
                            else
                            {
                                errAcq++;
                            }

                            if (profile->protocolQueueSize() > 0)
                            {
                                initA = false;
                            }
                        }
                        else
                        {
                            int thrResult = prepareThread(threadsV[i], profile->getProtocol());

                            if (thrResult == 0)
                            {
                                profile->remProtocolQueue();
                            }
                            else if (thrResult != 2 && thrResult != 0)
                            {
                                profile->remProtocolQueue();
                            }
                            else
                            {
                                errAcq++;
                            }

                            if (profile->appQueueSize() > 0)
                            {
                                initA = true;
                            }
                        }

                        i++;
                    }
                }
                else
                {
                    return 5;   // Fail to create the thread pointers
                }
            }
            catch (const std::exception& e)
            {
                std::cout << "Fail to load the profile!" << std::endl;
                std::cerr << e.what() << std::endl;

                return 4;   // Fail to load the profile
            }
        }
        else
        {
            std::cout << msg::writeError("Fail to get the profile " + profileName + ". Error code: " + std::to_string(chkProfileStatus)) << std::endl;

            return 3;   // Fail to get the profile from command line
        }
    }

    return 0;
}