#include "Editor_Explorer.h"
#include "Texture.h"
#include "Texture_OpenGL.h"

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

  std::string current_path = MX_RESOURCES;
  const std::string lowest_path = MX_RESOURCES;

  void load_directory(const char* path)
  {
    static ImGui_Icon folder_icon("icons/folder2.png", 20.0f, 20.0f);
    static ImGui_Icon txt_icon("icons/txt.png", 20.0f, 20.0f);
    static ImGui_Icon png_icon("icons/png.png", 20.0f, 20.0f);
    static ImGui_Icon jpg_icon("icons/jpg.png", 20.0f, 20.0f);
    static ImGui_Icon unknown_icon("icons/unkown.png", 20.0f, 20.0f);

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
            txt_icon.render();
          else if (file_extension == ".png")
            png_icon.render();
          else if (file_extension == ".jpg")
            jpg_icon.render();
          else
            unknown_icon.render();

          ImGui::SameLine(0.0f, 2.0f);

          if (ImGui::Button(file_name.c_str()))
          {
            
          }

          static ImGui_ContextMenu explorer_context_menu("Explorer Context Menu");
          if (explorer_context_menu.begin())
          {
            static char buffer[128];
            ImGui::InputText("##rename file or folder", buffer, IM_ARRAYSIZE(buffer));
        
            ImGui::SameLine();
            if (ImGui::Button("Rename") && file_name.length() > 0)
            {
              std::string old_full_path = full_path;
              full_path = full_path.substr(0, found_name + 1) + buffer;
              file_name = buffer;
              boost::filesystem::rename(old_full_path, full_path);
            }

            if (ImGui::Button("Delete"))
            {
              // make a popup to confirm pop up LOL XD
             // m_popup_delete.open();
            }

            explorer_context_menu.end();
          }
          
        }
        
      }
    }
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
          if (ImGui::BeginMenu("Back"))
          {
            auto found = current_path.find_last_of('/');
            current_path = current_path.substr(0, found);
            
            ImGui::EndMenu();
          }
        }
        
        ImGui::EndMenuBar();
      }
      /*
      TODO:
        add boost directory function that gets all files and directories
      */

      load_directory(current_path.c_str());
      
    }

    ImGui_Window::end();
  }

}