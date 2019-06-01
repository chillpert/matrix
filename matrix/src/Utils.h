#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

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
}

#endif // UTILS_H