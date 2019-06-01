#include "matrix/src/platform/gui/GUI_ImGui_Flags.h"

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

  std::vector<char*> all_available_models = {""};
  std::vector<const char*> all_current_scenes;
  std::vector<std::string> active_objects_s;

  int item_objects_to_spawn = 0;
  int item_objects_to_select = 0;

  void reset_window_naming()
  {
    event_window_title = default_window_title;
    event_window_message = default_window_message;
    event_window_button = default_button_label;
  }

  void check_folder_for_objects()
  {
    std::string model_path = MX_MODEL_PATH;
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
  }
}