#include "Editor_Explorer.h"
#include "Texture.h"
#include "Texture_OpenGL.h"
#include "Application.h"

#ifdef MX_PLATFORM_UNIX_X64
  #include <boost/filesystem.hpp>
  #include <boost/range/iterator_range.hpp>
#elif MX_PLATFORM_WINDOWS_X64
  #include <boost/filesystem.hpp>
  #include <boost/range/iterator_range.hpp>
#endif

namespace MX
{
  std::string single_clicked_file_name;
  std::string single_clicked_full_path;
  std::string double_clicked_file_name;
  std::string double_clicked_full_path;
  bool show_explorer_context_menu = false;
  bool show_file_inspector_context_menu = false;
  bool can_be_displayed = false;
  bool enlarged_picture_update = false;
  std::string file_extension;

  static bool sort_by_name = false;
  static bool sort_by_file = false;

  Editor_Explorer::Editor_Explorer(const char* name, ImGuiWindowFlags flags)
  {
    initialize(name, flags);
  }

  bool Editor_Explorer::initialize(const char* name, ImGuiWindowFlags flags)
  {
    return ImGui_Window::initialize(name, flags);
  }

  bool Editor_Explorer::update()
  {
    return ImGui_Window::update();
  }

  void Editor_Explorer::render()
  {
    if (ImGui_Window::begin())
    {
      if (ImGui::BeginMenuBar())
      {
        if (ImGui::BeginMenu("Sort"))
        {
          if (ImGui::MenuItem("Name", "", &sort_by_name))
          {
            sort_by_file = false;
            refresh_directory();

          }

          if (ImGui::MenuItem("File", "", &sort_by_file))
          {
            sort_by_name = false;
            refresh_directory();
          }

          ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("New"))
        {
          if (ImGui::MenuItem("Scene"))
          {
            MX_WORLD.push(std::make_shared<Scene>("New Scene.mx"), true, true);

            refresh_directory();
          }

          if (ImGui::MenuItem("Folder"))
          {
            // initially set to end with '/', but boost does not add '/' to the end of the path - add it manually
            if (current_path[current_path.size() - 1] != '/')
              current_path += '/';

            boost::filesystem::create_directory(current_path + Utility::get_unique_folder_name("folder", current_path));
            
            refresh_directory();
          }

          if (ImGui::MenuItem("Material"))
          {
            // initially set to end with '/', but boost does not add '/' to the end of the path - add it manually
            if (current_path[current_path.size() - 1] != '/')
              current_path += '/';

            std::ofstream file(current_path + Utility::get_unique_file_name("material.mat"));

            refresh_directory();
          }

          if (ImGui::MenuItem("Shader"))
          {
            // initially set to end with '/', but boost does not add '/' to the end of the path - add it manually
            if (current_path[current_path.size() - 1] != '/')
              current_path += '/';

            std::ofstream file(current_path + Utility::get_unique_file_name("shader.frag"));

            refresh_directory();
          }

          ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
      }

      static ImGui_Icon back_button("back.png", 15.0f, 15.0f);
      
      if (back_button.render_as_button())
      {
        // can not go further back than root directory
        if (current_path.length() > lowest_path.length())
        { 
          auto found = current_path.find_last_of('/');
          current_path = current_path.substr(0, found);
        }

        refresh_directory();
      }

      ImGui::SameLine();

      static ImGui_Icon home_button("house.png", 15.0f, 15.0f);

      if (home_button.render_as_button())
      {
        current_path = lowest_path;
        refresh_directory();
      }

      ImGui::SameLine();

      static ImGui_Icon refresh_button("reload.png", 15.0f, 15.0f);

      if (refresh_button.render_as_button())
      {
        refresh_directory();
      }

      ImGui::SameLine();
      
      if (ImGui::Button("Unselect##UnselectFileInExplorer"))
        m_selection.clear();

      ImGui::Separator();
      ImGui::Spacing();

      update_directory(current_path.c_str());
      render_directory();
    }

    ImGui_Window::end();
  }

  void Editor_Explorer::update_directory(const char* path)
  {
    if (m_update_items_in_directory)
    {
      boost::filesystem::path p(path);
      
      if (boost::filesystem::is_directory(p))
      {
        boost::filesystem::directory_iterator end_itr;

        for (boost::filesystem::directory_iterator itr(p); itr != end_itr; ++itr)
        {
          std::string full_path = itr->path().string();
          
        #ifdef MX_PLATFORM_WINDOWS_X64
          auto found = full_path.find_last_of('\\');
          full_path.at(found) = '/';
        #endif
          
          std::string file_name = full_path;
          auto found_name = full_path.find_last_of('/');
          file_name = file_name.substr(found_name + 1);
          
          if (boost::filesystem::is_directory(itr->path()))
          {
            m_items_in_directory.push_back({file_name, full_path, true});
          }
          else
          {
            m_items_in_directory.push_back({file_name, full_path, false});
          }
        }

        if (sort_by_name)
        {
          std::sort(m_items_in_directory.begin(), m_items_in_directory.end(), [](auto& a, auto& b){
            return std::get<0>(a) < std::get<0>(b);
          });
        }
        else if (sort_by_file)
        {
          std::sort(m_items_in_directory.begin(), m_items_in_directory.end(), [](auto& a, auto& b){
            return Utility::get_file_ending(std::get<0>(a)) < Utility::get_file_ending(std::get<0>(b));
          });
        }
      }

      m_update_items_in_directory = false;
    }
  }

  void Editor_Explorer::render_directory()
  {
    static ImGui_Icon folder_icon("folder2.png", 20.0f, 20.0f);
    static ImGui_Icon txt_icon("txt.png", 20.0f, 20.0f);
    static ImGui_Icon png_icon("png.png", 20.0f, 20.0f);
    static ImGui_Icon jpg_icon("jpg.png", 20.0f, 20.0f);
    static ImGui_Icon unknown_icon("unknown.png", 20.0f, 20.0f);
    static ImGui_Icon mx_icon("matrix_movie.png", 20.0f, 20.0f);
    static ImGui_Icon vert_icon("unknown.png", 20.0f, 20.0f);
    static ImGui_Icon frag_icon("unknown.png", 20.0f, 20.0f);

    for (auto& item : m_items_in_directory)
    {
      // is a folder
      if (std::get<2>(item) == true)
      {
        // render folder icon
        folder_icon.render();
        ImGui::SameLine(0.0f, 2.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.0f);

        if (ImGui::Button(std::get<0>(item).c_str()))
        {
          current_path = std::get<1>(item).c_str();

          refresh_directory();
        }

        ImGui::PopStyleVar();
      }
      // is a file
      else
      {
        // get file extension and apply icons respectively
        file_extension = Utility::get_file_ending(std::get<0>(item));

        if (file_extension == ".txt")
          txt_icon.render();
        else if (file_extension == ".png")
          png_icon.render();
        else if (file_extension == ".jpg")
          jpg_icon.render();
        else if (file_extension == ".mx")
          mx_icon.render();
        else if (file_extension == ".vert") // TODO needs icon
          vert_icon.render();
        else if (file_extension == ".frag") // TODO needs icon
          frag_icon.render();
        else
          unknown_icon.render();

        ImGui::SameLine(0.0f, 2.0f);

        bool file_name_in_selection = false;
        for (const std::string& it : m_selection)
        {
          if (it == std::get<0>(item))
            file_name_in_selection = true;
        }

        if (file_name_in_selection)
          ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
        else
          ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.26f, 0.26f, 0.26f, 1.0f));

        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.0f);

        if (ImGui::Button(std::get<0>(item).c_str()))
        {
          // add to vector only if shift is pressed
          if (ImGui::GetIO().KeyShift)
            m_selection.push_back(std::get<0>(item));
          else
          {
            m_selection.clear();
            m_selection.push_back(std::get<0>(item));
          }

          single_clicked_file_name = std::get<0>(item);
          single_clicked_full_path = std::get<1>(item);
        }

        ImGui::PopStyleVar();
        ImGui::PopStyleColor();

        setup_drag_drop_source(std::get<0>(item), current_path);

        // right click file to rename, copy, cut or delete it
        if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))
        {
          double_clicked_file_name = std::get<0>(item);
          double_clicked_full_path = std::get<1>(item);

          show_explorer_context_menu = true;
          show_file_inspector_context_menu = false;
        }

        // double click on e.g. images to see what is inside
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
        {
          double_clicked_file_name = std::get<0>(item);
          double_clicked_full_path = std::get<1>(item);

          // load scene
          if (file_extension == ".mx")
            MX_WORLD.load_scene(std::get<0>(item));
          // open text files
          else if (file_extension == ".vert" || file_extension == ".frag" || file_extension == ".txt")
          {
            GUI_MODULES.at("Editor")->open();

            // display file content
            auto editor_ptr = std::dynamic_pointer_cast<Editor_Editor>(GUI_MODULES.at(Constants::Modules::editor_name));
            editor_ptr->set_input(double_clicked_full_path);
          }
          else
          {
            enlarged_picture_update = true;
            show_file_inspector_context_menu = true;
            show_explorer_context_menu = false;
          }
        }
      }
    }

    if (double_clicked_file_name.length() > 0)
    {
      // render double click context menu (file inspector)
      static ImGuiWindowFlags flags_context_menu = 
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar;

      static ImGui_Popup file_inspector("File Inspector", flags_context_menu);
      if (show_file_inspector_context_menu)
      {
        show_file_inspector_context_menu = false;
        file_inspector.open();
      }

      if (file_inspector.begin())
      {
        /*
          TODO:
            - this should not be an icon but instead an actual texture (use ImGui::Image) (maybe write utility class for this)
        */

        // remove file name from full path temporarily since texture class does weird things with the naming
        //static ImGui_Icon enlarged_picture(double_clicked_file_name, double_clicked_full_path.substr(0, double_clicked_full_path.length() - double_clicked_file_name.length()));

        if (enlarged_picture_update)
        {
          //enlarged_picture = ImGui_Icon(double_clicked_file_name, double_clicked_full_path.substr(0, double_clicked_full_path.length() - double_clicked_file_name.length()));
          enlarged_picture_update = false;
        }

        //enlarged_picture.render();
        file_inspector.end();
      }

      // render right click context menu (properties)
      static ImGui_Popup context_menu("ContextMenuFileExplorerPopup");
      if (show_explorer_context_menu)
      {
        show_explorer_context_menu = false;
        context_menu.open();
      }

      static bool close_context_menu = false;
      static bool show_rename_field = false;

      if (context_menu.begin())
      {
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.0f);

        if (ImGui::Button("Rename", ImVec2(75.0f, 0.0f)))
        {
          show_rename_field = true;          
        }

        if (show_rename_field)
        {
          static ImGui_InputText rename_field("##Rename file or folder");
          ImGui::SetNextItemWidth(75.0f);
          bool enter_pressed = rename_field.render(double_clicked_file_name);

          if (enter_pressed && double_clicked_file_name.length() > 0)
          {
            show_rename_field = false;

            std::string original_file_name = double_clicked_file_name; 
            // check if new file name has a point in it
            std::string buffer_str = rename_field.m_buffer;
            auto found_point = buffer_str.find('.');
            if (found_point != std::string::npos)
            {
              // check if new file name has at least one letter after point
              std::string assertion = buffer_str.substr(found_point);
              if (assertion.length() > 1)
              {
                // check if new file name has at least one letter before point
                assertion = buffer_str.substr(0, found_point);
                if (assertion.length() > 0)
                {
                  std::string old_full_path = double_clicked_full_path; 
                  auto found_name = double_clicked_full_path.find_last_of('/');

                  double_clicked_full_path = double_clicked_full_path.substr(0, found_name + 1) + rename_field.m_buffer;
                  double_clicked_file_name = rename_field.m_buffer;

                  if (double_clicked_file_name.find(".mx") != std::string::npos)
                  {
                    if (!MX_WORLD.rename_scene(old_full_path, double_clicked_full_path))
                      MX_WARN("MX: Scene: Can not rename a scene that has not been loaded.");
                  }
                  else
                  {
                    boost::filesystem::rename(old_full_path, double_clicked_full_path);
                    refresh_directory();
                  }
                }
              }
            }
          }
        }

        static ImGui_Popup m_popup_delete("ExplorerConfirmDeletion");
        if (ImGui::Button("Delete", ImVec2(75.0f, 0.0f)))
        {
          m_popup_delete.open();
        }

        if (close_context_menu)
        {
          close_context_menu = false;
          show_rename_field = false;
          m_popup_delete.close();
        }

        if (ImGui::Button("Copy", ImVec2(75.0f, 0.0f))) { }
        if (ImGui::Button("Cut", ImVec2(75.0f, 0.0f))) { }

        ImGui::PopStyleVar();

        if (m_popup_delete.beginModal())
        {
          ImGui::Text("This change can not be undone. Are you sure to proceed?");
          
          if (ImGui::Button("No"))
          {
            m_popup_delete.close();
          }

          ImGui::SameLine();

          if (ImGui::Button("Yes"))
          {
            refresh_directory();

            m_popup_delete.close();
            close_context_menu = true;

            // handle different delete operations based on the file
            std::string file_ending = Utility::get_file_ending(double_clicked_file_name);

            if (file_ending == ".mx")
            {
              if (!MX_WORLD.remove_scene(double_clicked_file_name))
              {
                MX_AASSERT(MX_WORLD.remove_scene_file(double_clicked_full_path), "MX: GUI: Failed to delete scene");
              }
            }
            else
            {
              MX_INFO_LOG("MX: GUI: Explorer: Deleting file: " + double_clicked_full_path);
              boost::filesystem::remove(double_clicked_full_path);
            }
          }
          
          m_popup_delete.end();
        }

        context_menu.end();
      }
      else
        show_rename_field = false;
    }
  }

  void Editor_Explorer::refresh_directory()
  {
    m_items_in_directory.clear();
    m_update_items_in_directory = true;
  }

  void Editor_Explorer::setup_drag_drop_source(const std::string& file_name, const std::string& file_path)
  {
    static std::string data_type_to_send = "";

    if (ImGui::IsMouseDown(0) && ImGui::IsItemClicked(0))
    {
      auto tag_vert = file_name.find(".vert");
      auto tag_frag = file_name.find(".frag");
      auto tag_png = file_name.find(".png");
      auto tag_jpg = file_name.find(".jpg");
      auto tag_jpeg = file_name.find(".jpeg");
      auto tag_obj = file_name.find(".obj");

      if (tag_vert != std::string::npos || tag_frag != std::string::npos)
        data_type_to_send = "SHADER";
      else if (tag_png != std::string::npos || tag_jpg != std::string::npos || tag_jpeg != std::string::npos)
        data_type_to_send = "IMAGE";
      else if (tag_obj != std::string::npos)
        data_type_to_send = "OBJECT";
      else
        data_type_to_send = "UNDEF";
    }

    // allows file to be dragged somewhere
    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
    {
      std::string send_tag = data_type_to_send + "_FE"; // FE = File Explorer
      std::string send_message = file_path + "/" + file_name;
      ImGui::SetDragDropPayload(send_tag.c_str(), send_message.c_str(), sizeof(char) * 200);    // Set payload to carry the index of our item (could be anything)
      ImGui::EndDragDropSource();
    }
  }
}