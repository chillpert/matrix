#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <chrono>

namespace MX
{
  const int initial_window_width = 1200;
  const int initial_window_height = 600;

  const uint64_t max_amount_of_objects_per_scene = 999999;

  extern int max_window_width;
  extern int max_window_height;

  const std::string default_root_name = "Root";
  const std::string default_shader_name = "blinn_phong";
  const std::string glsl_version = "#version 330 core";

  std::string parse_file(const std::string &path);
  std::string tokenizeLine(const std::string &delimiter);
  std::string f_str(float num);
  std::string f_str(float num, float num_decimals);

  std::string remove_file_ending(const std::string &name);
  std::string get_file_ending(const std::string& file);
  std::string get_file_name(const std::string& path);

  

  void assert_condition(bool condition, const char* message);
  void find_all_files_of_same_type(const char* path, std::vector<std::string>* results, const std::string& type, bool only_file_name = 1);

  uint64_t generate_id();

#ifdef MX_PLATFORM_WINDOWS_X64
  extern std::chrono::time_point<std::chrono::steady_clock> current_time;
#elif MX_PLATFORM_UNIX_X64
  extern std::chrono::_V2::system_clock::time_point current_time;
#endif
}

#endif // UTILS_H