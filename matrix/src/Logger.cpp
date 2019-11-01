#include <Logger.h>

#define _CRT_SECURE_NO_WARNINGS
#ifdef MX_PLATFORM_WINDOWS_X64
  #include <windows.h>
#endif

#ifdef MX_IMGUI_ACTIVE
  #include <GUI_ImGui_Flags.h>
#endif

// global macros for debugging
#ifdef MX_DEBUG
  #define MX_LOG_FATAL   "FATAL  [" + t + "]: " + message + "\n"
  #define MX_LOG_WARN    "WARNING[" + t + "]: " + message + "\n"
  #define MX_LOG_INFO    "INFO   [" + t + "]: " + message + "\n"
  #define MX_LOG_SUCCESS "SUCCESS[" + t + "]: " + message + "\n"

  #ifdef MX_GUI_LOG_ALL
    #define MX_WRITE_TO_GUI(x, y) writeToGUI(x, y)
  #else
    #define MX_WRITE_TO_GUI(x, y)
  #endif

  #define MX_GUI_FATAL   "[" + t + "]: " + message + "\n"
  #define MX_GUI_WARN    "[" + t + "]: " + message + "\n"
  #define MX_GUI_INFO    "[" + t + "]: " + message + "\n"
  #define MX_GUI_SUCCESS "[" + t + "]: " + message + "\n"

  #ifdef MX_PLATFORM_UNIX_X64
    #define MX_PRINT_TO_CONSOLE(x) std::cerr << finalMessage.substr(12)
  #elif MX_PLATFORM_WINDOWS_X64
    #define MX_PRINT_TO_CONSOLE(x) std::cerr << finalMessage.substr(7)
  #endif

  #ifdef MX_PLATFORM_WINDOWS_X64
    #define MX_CONSOLE_HANDLE HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #define MX_PRINT_FATAL    SetConsoleTextAttribute(hConsole, 12); std::string finalMessage = "FATAL  [" + t + "]: " + message + "\n";
    #define MX_PRINT_WARN     SetConsoleTextAttribute(hConsole, 14); std::string finalMessage = "WARNING[" + t + "]: " + message + "\n";
    #define MX_PRINT_INFO     SetConsoleTextAttribute(hConsole, 8); std::string finalMessage = "INFO   [" + t + "]: " + message + "\n";
    #define MX_PRINT_SUCCESS  SetConsoleTextAttribute(hConsole, 2); std::string finalMessage = "SUCCESS[" + t + "]: " + message + "\n";
    #define MX_PRINT_RESET    SetConsoleTextAttribute(hConsole, 7);
  #elif MX_PLATFORM_UNIX_X64
    #define MX_CONSOLE_HANDLE
    #define MX_PRINT_FATAL    std::string finalMessage = "\033[31mFATAL  \033[31m[" + t + "]: " + message + "\033[0m\n";
    #define MX_PRINT_WARN     std::string finalMessage = "\033[33mWARNING\033[33m[" + t + "]: " + message + "\033[0m\n";
    #define MX_PRINT_INFO     std::string finalMessage = "\033[90mINFO   \033[90m[" + t + "]: " + message + "\033[0m\n";
    #define MX_PRINT_SUCCESS  std::string finalMessage = "\033[32mSUCCESS\033[32m[" + t + "]: " + message + "\033[0m\n";
    #define MX_PRINT_RESET
  #endif
#else
  #define MX_CONSOLE_HANDLE   std::string finalMessage;
  #define MX_PRINT_FATAL      std::string finalMessage;
  #define MX_PRINT_WARN       std::string finalMessage;
  #define MX_PRINT_INFO       std::string finalMessage;
  #define MX_PRINT_SUCCESS    std::string finalMessage;
  #define MX_PRINT_RESET

  #define MX_LOG_FATAL   finalMessage
  #define MX_LOG_WARN    finalMessage
  #define MX_LOG_INFO    finalMessage
  #define MX_LOG_SUCCESS finalMessage

  #define MX_WRITE_TO_GUI(x, y)

  #define MX_GUI_FATAL
  #define MX_GUI_WARN
  #define MX_GUI_INFO
  #define MX_GUI_SUCCESS

  #define MX_PRINT_TO_CONSOLE(x)
#endif

namespace MX
{
  MX_CONSOLE_HANDLE;

  auto start_time = std::chrono::high_resolution_clock::now();

  static bool clearFlag = 1;

  void Logger::writeToFile(const std::string &message)
  {
    if (clearFlag)
    {
      remove("resources/log.txt");
      clearFlag = 0;
    }
    std::ofstream logFile;
    logFile.open("resources/log.txt", std::ios::app);
    logFile << message;
    logFile.close();
  }

  void Logger::writeToGUI(const std::string &message, const logger_message_type &t)
  {
  #ifdef MX_IMGUI_ACTIVE
    ImVec4 color(0.7f, 0.7f, 0.7f, 1.0f);

    switch (t)
    {
      case mx_fatal:
      {
        color = {1.0f, 0.0f, 0.0f, 1.0f};
        break;
      }
      case mx_info:
      case mx_warn:
      case mx_success:
      default:
      {
        break;
      }
    }

    get_messages_gui().push_back(std::make_tuple(message, color, t));
  #endif
  }

  std::string Logger::getTime()
  {
  #ifdef MX_PLATFORM_UNIX_X64
    current_time = std::chrono::_V2::high_resolution_clock::now();
  #elif MX_PLATFORM_WINDOWS_X64
    current_time = std::chrono::high_resolution_clock::now();
  #endif
    int64_t h = std::chrono::duration_cast<std::chrono::hours>(current_time - start_time).count();
    int64_t m = std::chrono::duration_cast<std::chrono::minutes>(current_time - start_time).count() % 60;
    int64_t s = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count() % 60;

    std::string sec;
    std::string min;
    std::string hour;

    if (s < 10)
      sec = "0" + std::to_string(s);
    else
      sec = std::to_string(s);

    if (m < 10)
      min = "0" + std::to_string(m);
    else
      min = std::to_string(m);

    if (h < 10)
      hour = "0" + std::to_string(h); 
    else
      hour = std::to_string(h);
    
    return hour + ":" + min + ":" + sec;
  }

  void Logger::p_Fatal(const std::string &message)
  {
    std::string t = getTime();
    MX_PRINT_FATAL;
    MX_PRINT_TO_CONSOLE(finalMessage);
    MX_PRINT_RESET;
    writeToFile(MX_LOG_FATAL);
    writeToGUI(MX_GUI_FATAL, mx_fatal);
  }

  void Logger::p_Warn(const std::string &message)
  {
    std::string t = getTime();
    MX_PRINT_WARN;
    MX_PRINT_TO_CONSOLE(finalMessage);
    MX_PRINT_RESET;
    writeToFile(MX_LOG_WARN);
    writeToGUI(MX_GUI_WARN, mx_warn);
  }

  void Logger::p_Info(const std::string &message)
  {
    std::string t = getTime();
    MX_PRINT_INFO;
    MX_PRINT_TO_CONSOLE(finalMessage);
    MX_PRINT_RESET;
    writeToFile(MX_LOG_INFO);
    writeToGUI(MX_GUI_INFO, mx_info);
  }

  void Logger::p_Success(const std::string &message)
  {
    std::string t = getTime();
    MX_PRINT_SUCCESS;
    MX_PRINT_TO_CONSOLE(finalMessage);
    MX_PRINT_RESET;
    writeToFile(MX_LOG_SUCCESS);
    writeToGUI(MX_GUI_SUCCESS, mx_success);
  }

  void Logger::p_Fatal_log(const std::string &message)
  {
    std::string t = getTime();
    writeToFile(MX_LOG_FATAL);
    MX_WRITE_TO_GUI(MX_GUI_FATAL, mx_fatal);
  }

  void Logger::p_Warn_log(const std::string &message)
  {
    std::string t = getTime();
    writeToFile(MX_LOG_WARN);
    MX_WRITE_TO_GUI(MX_GUI_WARN, mx_warn);
  }

  void Logger::p_Info_log(const std::string &message)
  {
    std::string t = getTime();
    writeToFile(MX_LOG_INFO);
    MX_WRITE_TO_GUI(MX_GUI_INFO, mx_info);
  }

  void Logger::p_Success_log(const std::string &message)
  {
    std::string t = getTime();
    writeToFile(MX_LOG_SUCCESS);
    MX_WRITE_TO_GUI(MX_GUI_SUCCESS, mx_success);
  }

  std::vector<std::tuple<std::string, ImVec4, logger_message_type>>& Logger::get_messages_gui()
  {
    static std::vector<std::tuple<std::string, ImVec4, logger_message_type>> m_messages_gui;
    return m_messages_gui;
  }
}