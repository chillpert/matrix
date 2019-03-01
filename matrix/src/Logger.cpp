#ifdef MX_DEBUG
    #ifdef MX_PLATFORM_WINDOWS_X64
        #define MX_CONSOLE_HANDLE HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        
        #define MX_PRINT_FATAL      SetConsoleTextAttribute(hConsole, 12);\
                                    std::string finalMessage = "FATAL  [" + t + "]: " + message + "\n";
        #define MX_PRINT_WARN       SetConsoleTextAttribute(hConsole, 14);\
                                    std::string finalMessage = "WARNING[" + t + "]: " + message + "\n";
        #define MX_PRINT_INFO       SetConsoleTextAttribute(hConsole, 8);\
                                    std::string finalMessage = "INFO   [" + t + "]: " + message + "\n";
        #define MX_PRINT_SUCCESS    SetConsoleTextAttribute(hConsole, 2);\
                                    std::string finalMessage = "SUCCESS[" + t + "]: " + message + "\n";
        #define MX_PRINT_RESET      SetConsoleTextAttribute(hConsole, 7);        
    #endif
#endif

#define _CRT_SECURE_NO_WARNINGS

#include "matrix/src/pch/stdafx.h"

namespace MX {
    
    MX_CONSOLE_HANDLE;

    static bool clearFlag = 1;

    void Logger::writeToFile(std::string message) {
        if (clearFlag) {
            remove("log.txt");
            clearFlag = 0;
        }
        std::ofstream logFile;
        logFile.open("log.txt", std::ios::app);
        logFile << message;
        logFile.close();
    }

    std::string Logger::getTime() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        std::string h = std::to_string(ltm->tm_hour);
        std::string m = std::to_string(ltm->tm_min);
        std::string s = std::to_string(ltm->tm_sec);
        return h + ":" + m + ":" + s;
    }

    void Logger::p_Fatal(std::string message) {
        std::string t = getTime();
        MX_PRINT_FATAL;
        std::cerr << finalMessage;
        MX_PRINT_RESET;
        writeToFile(finalMessage);
    }

    void Logger::p_Warn(std::string message) {
        std::string t = getTime();
        MX_PRINT_WARN;
        std::cerr << finalMessage;
        MX_PRINT_RESET;
        writeToFile(finalMessage);
    }

    void Logger::p_Info(std::string message) {
        std::string t = getTime();
        MX_PRINT_INFO;
        std::cerr << finalMessage;
        MX_PRINT_RESET;
        writeToFile(finalMessage);
    }

    void Logger::p_Success(std::string message) {
        std::string t = getTime();
        MX_PRINT_SUCCESS;
        std::cerr << finalMessage;
        MX_PRINT_RESET;
        writeToFile(finalMessage);
    }
}