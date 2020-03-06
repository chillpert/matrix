#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <chrono>

namespace MX
{
  namespace Constants
  {
    const int initial_window_width = 1200;
    const int initial_window_height = 600;
    const int max_screen_width = 1920;
    const int max_screen_height = 1080;
    const uint64_t max_amount_of_objects_per_scene = 999999;
    const std::string default_root_name = "Root";
    const std::string default_shader_name = "blinn_phong";
    const std::string glsl_version = "#version 330 core";
  }

  extern int max_window_width;
  extern int max_window_height;

  namespace Utility
  {
    std::string parse_file(const std::string &path);
    std::string tokenizeLine(const std::string &delimiter);
    std::string f_str(float num);
    std::string f_str(float num, float num_decimals);

    std::string remove_file_ending(const std::string &name);
    std::string get_file_ending(const std::string& file);
    std::string get_file_name(const std::string& path);
    void find_all_files_of_same_type(const char* path, std::vector<std::string>* results, const std::string& type, bool only_file_name = true);
    std::string get_unique_file_name(const std::string& name);

    uint64_t generate_id();
  }

  namespace Debug
  {
    void assert_condition(bool condition, const char* message);
  }
}

#endif // UTILS_H