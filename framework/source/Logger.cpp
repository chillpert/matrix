#ifdef PLATFORM_WINDOWS_X64
    #ifdef DEBUG
        #include "Logger.h"
        #include <fstream>
        #include <windows.h> 
        #include <ctime>
        #include <iostream>

        namespace Matrix {

            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

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
                SetConsoleTextAttribute(hConsole, 12);
                std::string finalMessage = "FATAL[" + t + "]: " + message + "\n";
                std::cerr << finalMessage;
                SetConsoleTextAttribute(hConsole, 7);
                writeToFile(finalMessage);
            }

            void Logger::p_Warn(std::string message) {
                std::string t = getTime();
                SetConsoleTextAttribute(hConsole, 14);
                std::string finalMessage = "WARNING[" + t + "]: " + message + "\n";
                std::cerr << finalMessage;
                SetConsoleTextAttribute(hConsole, 7);
                writeToFile(finalMessage);
            }

            void Logger::p_Info(std::string message) {
                std::string t = getTime();
                SetConsoleTextAttribute(hConsole, 8);
                std::string finalMessage = "INFO[" + t + "]: " + message + "\n";
                std::cerr << finalMessage;
                SetConsoleTextAttribute(hConsole, 7);
                writeToFile(finalMessage);
            }
        }
    #endif
#endif