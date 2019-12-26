#include "Editor_Explorer.h"
#include "Texture.h"
#include "Texture_OpenGL.h"

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
      static int first_iteration = 1;
      static ImTextureID my_tex_id;
      static float my_tex_w;
      static float my_tex_h;
      static MX_TEXTURE *derived_tex_ptr;

      if (first_iteration)
      {
        first_iteration = false;

        static std::unique_ptr<Texture> play_button(std::make_unique<MX_TEXTURE>("icons/folder2.png"));
        play_button->initialize();
        derived_tex_ptr = static_cast<MX_TEXTURE*>(play_button.get());

        my_tex_id = (void*)derived_tex_ptr->getID();
        my_tex_w = derived_tex_ptr->m_Stb.width / 25.0f;
        my_tex_h = derived_tex_ptr->m_Stb.height / 25.0f;
      }

      ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.0f));
      
      ImGui::SameLine();
      ImGui::Button("Resources");
      
    }

    ImGui_Window::end();
  }

}