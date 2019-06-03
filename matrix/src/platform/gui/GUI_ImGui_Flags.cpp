#include "matrix/src/platform/gui/GUI_ImGui_Flags.h"
#include "matrix/src/layers/World.h"

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

namespace MX
{
  InputTypes currentInputType = mx_name;
  SelectionTypes currentSelectionType = mx_null;

  const std::string default_window_title = "undefined window title";
  const std::string default_window_message = "undefined window message";
  const std::string default_button_label = "undefined button label";

  std::string event_window_title = default_window_title;
  std::string event_window_message = default_window_message;
  std::string event_window_button = default_button_label;

  std::vector<std::pair<std::string, ImVec4>> logger_messages_for_gui;

  bool event_window_enabled = 0;
  bool input_window_enabled = 0;
  bool selection_window_enabled = 0;
  bool menubar_enabled = 1;
  bool editor_window_enabled = 1;
  bool hierarchy_window_enabled = 1;
  bool logger_window_enabled = 1;

  bool p_open_editor = 1;
  bool p_open_hierarchy = 1;
  bool p_open_logger = 1;
  bool p_open_event = 1;

  std::vector<char*> all_available_models = {""};
  std::vector<const char*> all_current_scenes;
  std::vector<const char*> all_available_shaders = {""};
  std::vector<std::string> active_objects_s;

  int item_objects_to_spawn = 0;
  int item_objects_to_select = 0;
  int item_shaders_to_select = 0;

  void reset_window_naming()
  {
    event_window_title = default_window_title;
    event_window_message = default_window_message;
    event_window_button = default_button_label;
  }

  void check_folder_for_objects()
  {
    boost::filesystem::path p(MX_MODEL_PATH);

    std::vector<boost::filesystem::directory_entry> all_available_models_d;

    if (boost::filesystem::is_directory(p))
    {
      std::copy(boost::filesystem::directory_iterator(p), boost::filesystem::directory_iterator(), std::back_inserter(all_available_models_d));

      for (std::vector<boost::filesystem::directory_entry>::const_iterator it = all_available_models_d.begin(); it != all_available_models_d.end(); ++it)
      {
        std::string temp = (*it).path().string();
        std::size_t found_slash = temp.find_last_of("/");
        std::size_t found_point = temp.find_last_of(".");
        temp = temp.substr(found_slash + 1, found_point - found_slash - 1);
        
        char *file_name = new char[temp.size()  + 1];
        std::copy(temp.begin(), temp.end(), file_name);
        file_name[temp.size()] = '\0';

        all_available_models.push_back(file_name);
      }
    }

    MX_INFO_LOG("MX: Model: " + std::to_string(all_available_models.size()) + " files found");
  }

  void check_folder_for_shaders()
  {
    boost::filesystem::path p(MX_SHADER_PATH);

    std::vector<boost::filesystem::directory_entry> all_available_shaders_d;

    if (boost::filesystem::is_directory(p))
    {
      std::copy(boost::filesystem::directory_iterator(p), boost::filesystem::directory_iterator(), std::back_inserter(all_available_shaders_d));

      for (std::vector<boost::filesystem::directory_entry>::const_iterator it = all_available_shaders_d.begin(); it != all_available_shaders_d.end(); ++it)
      {
        std::string temp = (*it).path().string();
        std::size_t found_slash = temp.find_last_of("/");
        std::size_t found_point = temp.find_last_of(".");
        temp = temp.substr(found_slash + 1, found_point - found_slash - 1);
        
        char *file_name = new char[temp.size()  + 1];
        std::copy(temp.begin(), temp.end(), file_name);
        file_name[temp.size()] = '\0';

        bool shader_file_exists_already = 0;

        for (const auto &it : World::get().m_Shaders)
        {
          if (it.getName() == file_name)
            shader_file_exists_already = 1;
        }

        if (!shader_file_exists_already)
        {
          MX_SHADER temp(file_name);
          World::get().m_Shaders.push_back(temp);         
        }
      }
      
      MX_INFO_LOG("MX: Shader: " + std::to_string(World::get().m_Shaders.size()) + " files found");

      for (auto &it : World::get().m_Shaders)
      {
        all_available_shaders.push_back(it.getName().c_str());
        it.initialize();
      }

      std::cout << all_available_shaders.size() << std::endl;
    }    
  }
}