#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include <chrono>

namespace MX
{
  #ifdef MX_DEBUG
    #define MX_ASSERT(x,y)  MX::Debug::assert_condition(x, y)
    #define ASSERT(x,y)     Debug::assert_condition(x,y)
  #elif
    #define MX_ASSERT(x,y)
    #define ASSERT(x,y)
  #endif

  // always assert no matter release or debug
  #define MX_AASSERT(x,y)  MX::Debug::assert_condition(x, y)
  #define AASERT(x,y)      Debug::assert_condition(x,y)

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
    const std::string undefined_string = "__UNDEF__";

    namespace Modules
    {
      // names for GUI modules
      const char* const dockspace_name = "Dockspace";
      const char* const viewport_name = "Viewport";
      const char* const profiler_name = "Profiler";
      const char* const console_name = "Terminal";
      const char* const object_name = "Object";
      const char* const hierarchy_name = "Hierarchy";
      const char* const explorer_name = "Explorer";
      const char* const editor_name = "Editor";
    }

    namespace Icons
    {
      // for all buttons in menu bars etc.
      const float menu = 15.0f;

      // for all items in explorer
      const float compact = 20.0f;
      const float large = 50.0f;
    }
  }

  extern int max_window_width;
  extern int max_window_height;

  namespace Utility
  {
    bool write_file(const std::string& message, const std::string &path);
    bool write_file(const char* message, const std::string &path);
    std::string parse_file(const std::string &path);
    std::string tokenize_line(const std::string &delimiter);
    std::string f_str(float num);
    std::string f_str(float num, float num_decimals);

    std::string remove_file_ending(const std::string &name);
    std::string get_file_ending(const std::string& file);
    std::string get_file_name(const std::string& path);
    void find_all_files_of_same_type(const char* path, std::vector<std::string>* results, const std::string& type, bool only_file_name = true);
    std::string get_unique_folder_name(const std::string& name, const std::string& path);
    std::string get_unique_file_name(const std::string& name);

    uint64_t generate_id();
  }

  namespace Debug
  {
    void assert_condition(bool condition, const char* message);
  }
}

#endif // UTILITY_H