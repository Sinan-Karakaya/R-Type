/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CrashUtils
*/

#pragma once

#include "RType.hpp"
#include <SFML/Network.hpp>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <csignal>
#endif

namespace RType::Utils
{

    class CrashUtils
    {
    public:
        static void setupCatcher()
        {
#ifdef _WIN32
            SetUnhandledExceptionFilter(&CrashUtils::exceptionHandler);
#else
            signal(SIGSEGV, &CrashUtils::exceptionHandler);
            signal(SIGABRT, &CrashUtils::exceptionHandler);
#endif
        }

#ifdef _WIN32
        static LONG WINAPI exceptionHandler(EXCEPTION_POINTERS *exceptionInfo)
#else
        static void exceptionHandler(int signal)
#endif
        {
            std::cout << "Application crashed :(" << std::endl;
            std::cout << "Do you want to send a crash report ? (y/n) ";

            std::string input;
            std::cin >> input;
            if (input == "y") {
                std::cout << "Sending crash report..." << std::endl;
            } else {
                std::cout << "Crash report canceled" << std::endl;
#ifdef _WIN32
                return EXCEPTION_EXECUTE_HANDLER;
#else
                return;
#endif
            }

            std::vector<std::string> systemInfo;
#ifdef _WIN32
            SYSTEM_INFO sysInfo;
            GetSystemInfo(&sysInfo);

            systemInfo.push_back("Windows");
            systemInfo.push_back("Processor Architecture: " + std::to_string(sysInfo.wProcessorArchitecture));
            systemInfo.push_back("Processor Level: " + std::to_string(sysInfo.wProcessorLevel));
            systemInfo.push_back("Processor Revision: " + std::to_string(sysInfo.wProcessorRevision));
            systemInfo.push_back("Number of Processors: " + std::to_string(sysInfo.dwNumberOfProcessors));
            systemInfo.push_back("Page Size: " + std::to_string(sysInfo.dwPageSize));
            systemInfo.push_back("Active Processor Mask: " + std::to_string(sysInfo.dwActiveProcessorMask));
            systemInfo.push_back("Number of Processors: " + std::to_string(sysInfo.dwNumberOfProcessors));
            systemInfo.push_back("Processor Type: " + std::to_string(sysInfo.dwProcessorType));
            systemInfo.push_back("Allocation Granularity: " + std::to_string(sysInfo.dwAllocationGranularity));
#else
            systemInfo.push_back("Linux");
#endif
            std::vector<std::string> crashInfo;

#ifdef _WIN32
            crashInfo.push_back("Exception Code: 0x" + std::to_string(exceptionInfo->ExceptionRecord->ExceptionCode));
            crashInfo.push_back("Exception Flags: " + std::to_string(exceptionInfo->ExceptionRecord->ExceptionFlags));
            crashInfo.push_back("Exception Information: 0x" +
                                std::to_string((uint64_t)exceptionInfo->ExceptionRecord->ExceptionInformation));
#else
            crashInfo.push_back("Signal: " + std::to_string(signal));
#endif

            std::stringstream ss;
            ss << "R-Type Crash Report" << std::endl;
            ss << "===================" << std::endl;
            ss << std::endl;
            ss << "System Information" << std::endl;
            ss << "------------------" << std::endl;
            for (auto &info : systemInfo)
                ss << info << std::endl;
            ss << std::endl;
            ss << "Crash Information" << std::endl;
            ss << "------------------" << std::endl;
            for (auto &info : crashInfo)
                ss << info << std::endl;
            ss << std::endl;

            std::ofstream file("crash_report.txt");
            file << ss.str();
            file.close();

            sf::TcpSocket socket;
            if (socket.connect(sf::IpAddress("zertus.fr"), 40258) != sf::Socket::Done) {
                std::cout << "Failed to connect to crash report server" << std::endl;
#ifdef _WIN32
                return EXCEPTION_EXECUTE_HANDLER;
#else
                return;
#endif
            }

            if (socket.send(ss.str().c_str(), ss.str().size()) != sf::Socket::Done) {
                std::cout << "Failed to send crash report" << std::endl;
#ifdef _WIN32
                return EXCEPTION_EXECUTE_HANDLER;
#else
                return;
#endif
            }

            std::cout << "Crash report sent ! Quitting..." << std::endl;

#ifdef _WIN32
            return EXCEPTION_EXECUTE_HANDLER;
#else
            return;
#endif
        }
    };

} // namespace RType::Utils
