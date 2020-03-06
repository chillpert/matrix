#include "Utils.h"

#include <sstream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

namespace MX
{
  int max_window_width = 1920;
  int max_window_height = 1080;

#ifdef MX_PLATFORM_WINDOWS_X64
  std::chrono::time_point<std::chrono::steady_clock> current_time;
#elif MX_PLATFORM_UNIX_X64
  std::chrono::_V2::system_clock::time_point current_time;
#endif

  std::string parse_file(const std::string& path)
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

  std::string get_file_name(const std::string& path)
  {
    auto found_last_slash = path.find_last_of('/');
    
    std::string result = "__UNDEF__";

    if (found_last_slash != std::string::npos)
    {
      result = path.substr(found_last_slash + 1);  
    }
    else
      throw std::runtime_error("MX: Utils: Get File Name: Invalid path: " + path);
  
    return result;
  }



  void assert_condition(bool condition, const char* message)
  {
    if (!condition)
      throw std::runtime_error(message);
  }

  void find_all_files_of_same_type(const char* path, std::vector<std::string>* results, const std::string& type, bool only_file_name)
  {
    boost::filesystem::path p(path);

    // is a folder
    if (boost::filesystem::is_directory(p))
    {
      boost::filesystem::directory_iterator end_itr;

      for (boost::filesystem::directory_iterator itr(p); itr != end_itr; ++itr)
      {
        find_all_files_of_same_type(itr->path().c_str(), results, type);
      }
    }
    // is a file
    else
    {
      if (get_file_ending(path) == type)
      {
        if (only_file_name)
          results->push_back(get_file_name(path));
        else
          results->push_back(path);
      }
    }
  }

  uint64_t generate_id()
  {
    static uint64_t id = 0;
    return ++id;
  }
}

