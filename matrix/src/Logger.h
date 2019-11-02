#ifndef LOGGER_H
#define LOGGER_H

#ifdef MX_DEBUG
  // prints to console and logs to file
  #define MX_FATAL(x)   MX::Logger::p_Fatal(x)
  #define MX_WARN(x)    MX::Logger::p_Warn(x)
  #define MX_INFO(x)    MX::Logger::p_Info(x)
  #define MX_SUCCESS(x) MX::Logger::p_Success(x)
  // logs to file only
  #define MX_FATAL_LOG(x)   MX::Logger::p_Fatal_log(x)
  #define MX_WARN_LOG(x)    MX::Logger::p_Warn_log(x)
  #define MX_INFO_LOG(x)    MX::Logger::p_Info_log(x)
  #define MX_SUCCESS_LOG(x) MX::Logger::p_Success_log(x)
#else
  #define MX_FATAL(x) 
  #define MX_WARN(x) 
  #define MX_INFO(x)
  #define MX_SUCCESS(x)

  #define MX_FATAL_LOG(x)  
  #define MX_WARN_LOG(x)   
  #define MX_INFO_LOG(x)   
  #define MX_SUCCESS_LOG(x)
#endif

#include "Core.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <imgui.h>

namespace MX
{
  enum logger_message_type {
    mx_warn,
    mx_info,
    mx_success,
    mx_fatal,
    mx_all       // only used for gui-mx-logger
  };

  struct MX_API Logger
  {
    static std::string getTime();

    static void writeToFile(const std::string &message);
    static void writeToGUI(const std::string &message, const logger_message_type &t);

    static void p_Fatal(const std::string &message);
    static void p_Warn(const std::string &message);
    static void p_Info(const std::string &message);
    static void p_Success(const std::string &message);

    static void p_Fatal_log(const std::string &message);
    static void p_Warn_log(const std::string &message);
    static void p_Info_log(const std::string &message);
    static void p_Success_log(const std::string &message);
    
    static std::vector<std::pair<std::string, logger_message_type>>& get_messages_gui();
  };
}

#endif // LOGGER_H