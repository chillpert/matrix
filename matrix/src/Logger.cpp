#ifdef MX_DEBUG
  #define MX_LOG_FATAL   "FATAL  [" + t + "]: " + message + "\n"
  #define MX_LOG_WARN    "WARNING[" + t + "]: " + message + "\n"
  #define MX_LOG_INFO    "INFO   [" + t + "]: " + message + "\n"
  #define MX_LOG_SUCCESS "SUCCESS[" + t + "]: " + message + "\n"

  #ifdef MX_PLATFORM_WINDOWS_X64
    #define MX_CONSOLE_HANDLE HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #define MX_PRINT_FATAL    SetConsoleTextAttribute(hConsole, 12); std::string finalMessage = "FATAL  [" + t + "]: " + message + "\n";
    #define MX_PRINT_WARN     SetConsoleTextAttribute(hConsole, 14); std::string finalMessage = "WARNING[" + t + "]: " + message + "\n";
    #define MX_PRINT_INFO     SetConsoleTextAttribute(hConsole, 8); std::string finalMessage = "INFO   [" + t + "]: " + message + "\n";
    #define MX_PRINT_SUCCESS  SetConsoleTextAttribute(hConsole, 2); std::string finalMessage = "SUCCESS[" + t + "]: " + message + "\n";
    #define MX_PRINT_RESET    SetConsoleTextAttribute(hConsole, 7);        
  #elif MX_PLATFORM_UNIX_X64
    #define MX_CONSOLE_HANDLE
    #define MX_PRINT_FATAL    std::string finalMessage = "\033[31mFATAL  [" + t + "\033[31m]: " + message + "\033[0m\n"; 
    #define MX_PRINT_WARN     std::string finalMessage = "\033[33mWARNING[" + t + "]: " + message + "\033[0m\n";
    #define MX_PRINT_INFO     std::string finalMessage = "\033[90mINFO   [" + t + "]: " + message + "\033[0m\n";
    #define MX_PRINT_SUCCESS  std::string finalMessage = "\033[32mSUCCESS[" + t + "]: " + message + "\033[0m\n";
    #define MX_PRINT_RESET      
  #endif
#else
  #define MX_CONSOLE_HANDLE   std::string finalMessage;
  #define MX_PRINT_FATAL      std::string finalMessage;                        
  #define MX_PRINT_WARN       std::string finalMessage;                          
  #define MX_PRINT_INFO       std::string finalMessage;                           
  #define MX_PRINT_SUCCESS    std::string finalMessage;                  
  #define MX_PRINT_RESET        

  #define MX_LOG_FATAL   std::string finalMessage;
  #define MX_LOG_WARN    std::string finalMessage;
  #define MX_LOG_INFO    std::string finalMessage;
  #define MX_LOG_SUCCESS std::string finalMessage;
#endif

#define _CRT_SECURE_NO_WARNINGS

#include "matrix/src/pch/stdafx.h"

namespace MX
{
    
  MX_CONSOLE_HANDLE;

  static bool clearFlag = 1;

  void Logger::writeToFile(const std::string &message)
  {
    if (clearFlag)
    {
      remove("log.txt");
      clearFlag = 0;
    }
    std::ofstream logFile;
    logFile.open("log.txt", std::ios::app);
    logFile << message;
    logFile.close();
  }

  std::string Logger::getTime()
  {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::string h = std::to_string(ltm->tm_hour);
    std::string m = std::to_string(ltm->tm_min);
    std::string s = std::to_string(ltm->tm_sec);
    return h + ":" + m + ":" + s;
  }

  void Logger::p_Fatal(const std::string &message)
  {
    std::string t = getTime();
    MX_PRINT_FATAL;
    std::cerr << finalMessage;
    MX_PRINT_RESET;
    writeToFile(MX_LOG_FATAL);
  }

  void Logger::p_Warn(const std::string &message)
  {
    std::string t = getTime();
    MX_PRINT_WARN;
    std::cerr << finalMessage;
    MX_PRINT_RESET;
    writeToFile(MX_LOG_WARN);
  }

  void Logger::p_Info(const std::string &message)
  {
    std::string t = getTime();
    MX_PRINT_INFO;
    std::cerr << finalMessage;
    MX_PRINT_RESET;
    writeToFile(MX_LOG_INFO);
  }

  void Logger::p_Success(const std::string &message)
  {
    std::string t = getTime();
    MX_PRINT_SUCCESS;
    std::cerr << finalMessage;
    MX_PRINT_RESET;
    writeToFile(MX_LOG_SUCCESS);
  }

  void Logger::p_Fatal_log(const std::string &message)
  {
    std::string t = getTime();
    writeToFile(MX_LOG_FATAL);
  }

  void Logger::p_Warn_log(const std::string &message)
  {
    std::string t = getTime();
    writeToFile(MX_LOG_WARN);
  }

  void Logger::p_Info_log(const std::string &message)
  {
    std::string t = getTime();
    writeToFile(MX_LOG_INFO);
  }

  void Logger::p_Success_log(const std::string &message)
  {
    std::string t = getTime();
    writeToFile(MX_LOG_SUCCESS);
  }
}