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
  Editor_Explorer::Editor_Explorer(const std::string& name, ImGuiWindowFlags flags)
  {
    initialize(name, flags);
  }

  bool Editor_Explorer::initialize(const std::string& name, ImGuiWindowFlags flags)
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
          if (ImGui::MenuItem("Name"))
          {

          }

          if (ImGui::MenuItem("File"))
          {

          }

          ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("New"))
        {
          if (ImGui::MenuItem("File")) { }

          if (ImGui::MenuItem("Folder")) { }

          if (ImGui::MenuItem("Material")) { }

          if (ImGui::MenuItem("Shader")) { }

          ImGui::EndMenu();
        }

        // make sure user can not press back button to get out of resources folder
        if (current_path.length() > lowest_path.length())
        {
          if (ImGui::BeginMenu("Root"))
          {
            auto found = current_path.find_last_of('/');
            current_path = current_path.substr(0, found);
            
            ImGui::EndMenu();
          }
        }
        
        ImGui::EndMenuBar();
      }

      static ImGui_Icon home_button("back.png", 15.0f, 15.0f);
      if (current_path.length() > lowest_path.length())
      {
        if (home_button.render_as_button())
        {
          auto found = current_path.find_last_of('/');
          current_path = current_path.substr(0, found);
        }
      }

      load_directory(current_path.c_str());
    }

    ImGui_Window::end();
  }

  void Editor_Explorer::load_directory(const char* path)
  {
    static ImGui_Icon folder_icon("folder2.png", 20.0f, 20.0f);
    static ImGui_Icon txt_icon("txt.png", 20.0f, 20.0f);
    static ImGui_Icon png_icon("png.png", 20.0f, 20.0f);
    static ImGui_Icon jpg_icon("jpg.png", 20.0f, 20.0f);
    static ImGui_Icon unknown_icon("unkown.png", 20.0f, 20.0f);
    static ImGui_Icon mx_icon("matrix_movie.png", 20.0f, 20.0f);

    static std::string clicked_file_name;
    static std::string clicked_full_path;
    static bool show_explorer_context_menu = false;
    static bool show_file_inspector_context_menu = false;
    static bool can_be_displayed = false;
    static bool enlarged_picture_update = false;

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
          // render folder icon
          folder_icon.render();
          ImGui::SameLine(0.0f, 2.0f);

          if (ImGui::Button(file_name.c_str()))
          {
            current_path = full_path.c_str();
          }
        }
        else
        {
          // get file extension and apply icons respectively
          auto found_extension = file_name.find_last_of('.');
          std::string file_extension = file_name.substr(found_extension);

          if (file_extension == ".txt")
          {
            txt_icon.render();
            can_be_displayed = false;
          }
          else if (file_extension == ".png")
          {
            png_icon.render();
            can_be_displayed = true;
          }
          else if (file_extension == ".jpg")
          {
            jpg_icon.render();
            can_be_displayed = true;
          }
          else if (file_extension == ".mx")
          {
            mx_icon.render();
            can_be_displayed = false;
          }
          else
          {
            unknown_icon.render();
            can_be_displayed = false;
          }

          ImGui::SameLine(0.0f, 2.0f);

          if (ImGui::Button(file_name.c_str())) { }

          setup_drag_drop_source(file_name, current_path);
          
          // right click file to rename, copy, cut or delete it
          if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))
          {
            show_explorer_context_menu = true;
            show_file_inspector_context_menu = false;
            clicked_file_name = file_name;
            clicked_full_path = full_path;
          }

          // double click on e.g. images to see what is inside
          if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
          {
            // load scene
            if (file_extension == ".mx")
            {
              MX_INFO("MX: GUI: World: Loading scene: " + file_name);
              Application::get().m_World.load_scene(file_name);
            }
            else
            {
              enlarged_picture_update = true;
              show_file_inspector_context_menu = true;
              show_explorer_context_menu = false;
              clicked_file_name = file_name;
              clicked_full_path = full_path;
            }
          }
        }
      }

      if (clicked_file_name.length() > 0)
      {
        // render double click context menu (file inspector)
        static ImGuiWindowFlags flags_context_menu = 
          ImGuiWindowFlags_AlwaysAutoResize |
          ImGuiWindowFlags_NoCollapse |
          ImGuiWindowFlags_NoTitleBar;
          
        static ImGui_ContextMenu file_inspector("File Inspector", flags_context_menu);
        if (can_be_displayed)
        {
          if (file_inspector.begin(show_file_inspector_context_menu))
          {
            /*
              TODO:
                - this should not be an icon but instead an actual texture (use ImGui::Image) (maybe write utility class for this)
            */

            // remove file name from full path temporarily since texture class does weird things with the naming
            //static ImGui_Icon enlarged_picture(clicked_file_name, clicked_full_path.substr(0, clicked_full_path.length() - clicked_file_name.length()));

            if (enlarged_picture_update)
            {
              //enlarged_picture = ImGui_Icon(clicked_file_name, clicked_full_path.substr(0, clicked_full_path.length() - clicked_file_name.length()));
              enlarged_picture_update = false;
            }

            //enlarged_picture.render();
            file_inspector.end();
          }
        }

        // render right click context menu (properties)
        static ImGui_ContextMenu explorer_context_menu("Explorer Context Menu");

        if (explorer_context_menu.begin(show_explorer_context_menu))
        {
          static char buffer[128];
          ImGui::InputText("##rename file or folder", buffer, IM_ARRAYSIZE(buffer));

          ImGui::SameLine();
          if (ImGui::Button("Rename") && clicked_file_name.length() > 0)
          {
            // check if new file name has a point in it
            std::string buffer_str = buffer;
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
                  std::string old_full_path = clicked_full_path;

                  auto found_name = clicked_full_path.find_last_of('/');

                  clicked_full_path = clicked_full_path.substr(0, found_name + 1) + buffer;
                  clicked_file_name = buffer;
                  
                  boost::filesystem::rename(old_full_path, clicked_full_path);
                }
              }
            }
          }

          if (ImGui::Button("Delete"))
          {
            // make a popup to confirm pop up LOL XD
            // m_popup_delete.open();
          }

          if (ImGui::Button("Copy")) { }
          if (ImGui::Button("Cut")) { }

          explorer_context_menu.end();
        }   
      }  
    }
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