#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <chrono>

namespace MX
{
  enum logger_message_type
  {
    mx_warn,
    mx_info,
    mx_success,
    mx_fatal,
    mx_all       // only used for gui-mx-logger
  };
  
  std::string parseFile(const std::string &path);
  std::string tokenizeLine(const std::string &delimiter);

  const int initial_window_width = 1200;
  const int initial_window_height = 600;

  const std::string glsl_version = "#version 330";

  extern std::chrono::time_point<std::chrono::steady_clock> current_time;
}

#endif // UTILS_H