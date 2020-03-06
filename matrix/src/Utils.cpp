#include "Utils.h"

#include <sstream>
#include <fstream>

namespace MX
{
  int max_window_width = 1920;
  int max_window_height = 1080;

#ifdef MX_PLATFORM_WINDOWS_X64
  std::chrono::time_point<std::chrono::steady_clock> current_time;
#elif MX_PLATFORM_UNIX_X64
  std::chrono::_V2::system_clock::time_point current_time;
#endif
  std::string parseFile(const std::string& path)
  {
    std::ifstream stream(path);
    std::string line;
    std::stringstream ss[1];

    while (getline(stream, line))
    {
      ss[0] << line << '\n';
    }
    return ss[0].str();
  }

  std::string tokenizeLine(const std::string &delimiter)
  {
    return "";
  }

  std::string f_str(float num)
  {
    std::ostringstream buff;
    buff << num;
    return buff.str();
  }

  std::string f_str(float num, float num_decimals)
  {
    std::string temp = std::to_string(num);
    size_t found = temp.find('.');
    return temp.substr(0, found + static_cast<size_t>(num_decimals) + 1);
  }

/*
  const char* str_c(const std::string &str)
  {
    char test[str.size()];
    const char* temp;
  #ifdef MX_PLATFORM_UNIX_X64
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wformat-security"
    temp = str.c_str();
    #pragma GCC diagnostic pop
  #else
    temp = str.c_str();
  #endif
    return temp;
  }
*/

  std::string remove_file_ending(const std::string &name)
  {
    size_t hit = name.find_last_of('.');

    if (hit != std::string::npos)
      return name.substr(0, hit);

    return name;
  }

  std::string get_file_ending(const std::string& file)
  {
    auto found_extension = file.find_last_of('.');

    if (found_extension != std::string::npos)
      return file.substr(found_extension);
    // is a directory
    else
      return ".d";
  }

  uint64_t generate_id()
  {
    static uint64_t id = 0;
    return ++id;
  }
}

