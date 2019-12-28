#ifndef GUI_IMGUI_ICON_H
#define GUI_IMGUI_ICON_H

#include "stdafx.h"
#include "Texture.h"
#include "Texture_OpenGL.h"

namespace MX
{
  class ImGui_Icon
  {
  public:
    // if user did not set a custom size, use maximum size
    MX_API ImGui_Icon() = default;
    MX_API ImGui_Icon(const std::string& name, const std::string& path, float size_x = -1.0f, float size_y = -1.0f);
    MX_API ImGui_Icon(const std::string& path, float size_x = -1.0f, float size_y = -1.0f);

    MX_API void render();

    MX_API void set_corners(const ImVec2& uv0, const ImVec2& uv1);
    MX_API void set_tint_color(const ImVec4& tint_color);
    MX_API void set_border_color(const ImVec4& border_color);
  
  private:
    MX_API void initialize();

    MX_TEXTURE *m_derived_tex_ptr;
    ImTextureID m_tex_id;

    // defines top left and bottom right corner
    ImVec2 m_uv0;
    ImVec2 m_uv1;

    ImVec4 m_tint_col;
    ImVec4 m_border_col;

  public:
    std::string m_name;
    std::string m_path;
    float m_size_x;
    float m_size_y;

    std::unique_ptr<Texture> m_texture;
  };
}

#endif // GUI_IMGUI_ICON_H