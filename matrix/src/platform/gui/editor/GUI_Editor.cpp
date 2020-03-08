#include "GUI_Editor.h"
#include "Application.h"

namespace MX
{
  ImFont* font_global;

  GUI_Editor::GUI_Editor() { }

  void GUI_Editor::initialize()
  {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.IniFilename = MX_IMGUI_DEFAULT_INI_PATH "gui_default_layout.ini";
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    std::string font_file = MX_FONTS_PATH + std::string("DroidSans.ttf");
    font_global = io.Fonts->AddFontFromFileTTF(font_file.c_str(), 15.0f);

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowBorderSize = 0.0f;
    style.WindowBorderSize = 1.0f;
    style.WindowRounding = 0.0f;
    style.FrameRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.PopupRounding = 4.0f;
    style.ScrollbarRounding = 4.0f;

    ImVec4* colors = ImGui::GetStyle().Colors;

    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.41f, 0.41f, 0.41f, 0.31f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.59f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.36f, 0.35f, 0.35f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.23f, 0.23f, 0.23f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_DockingPreview] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.80f, 0.35f, 0.02f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    GUI_ImGui::initialize();

    // create modules
    auto dockspace = std::make_shared<Editor_Dock>(Constants::Modules::dockspace_name, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking);
    auto viewport = std::make_shared<Editor_Viewport>(Constants::Modules::viewport_name, ImGuiWindowFlags_MenuBar);
    //auto profiler = std::make_shared<Editor_Profiler>(Constants::Modules::profiler_name, ImGuiWindowFlags_MenuBar);
    auto console = std::make_shared<Editor_Console>(Constants::Modules::console_name, ImGuiWindowFlags_MenuBar);
    auto object = std::make_shared<Editor_Object>(Constants::Modules::object_name);
    auto hierarchy = std::make_shared<Editor_Hierarchy>(Constants::Modules::hierarchy_name, ImGuiWindowFlags_MenuBar);
    auto explorer = std::make_shared<Editor_Explorer>(Constants::Modules::explorer_name, ImGuiWindowFlags_MenuBar);
    auto editor = std::make_shared<Editor_Editor>(Constants::Modules::editor_name, ImGuiWindowFlags_MenuBar);
    
    // makes editor not show up by default
    editor->close();
    //profiler->close();

    m_visibilities = {&dockspace->m_visibilities};

    // toggle window visibility
    dockspace->set_visibilities({
      viewport->visibilty(),
      //profiler->visibilty(),
      console->visibilty(),
      object->visibilty(),
      hierarchy->visibilty(),
      explorer->visibilty(),
      editor->visibilty()
    });

    // set style variables for modules
    viewport->push_style(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    // add single modules to vector
    m_modules = {
      {dockspace->m_name, dockspace},
      {viewport->m_name, viewport},
      //{profiler->m_name, profiler},
      {console->m_name, console},
      {object->m_name, object},
      {hierarchy->m_name, hierarchy},
      {explorer->m_name, explorer},
      {editor->m_name, editor}
    };
  }

  void GUI_Editor::update()
  {
    GUI_ImGui::update();
    
    // update modules
    for (auto it : m_modules)
      it.second->update();
  }

  void GUI_Editor::render()
  {
    // set font
    ImGui::PushFont(font_global);
    ImGui::PopFont();

    // render modules
    for (auto it : m_modules)
      it.second->render();

    GUI_ImGui::render();
  }

  void GUI_Editor::clean()
  {
    GUI_ImGui::clean();
  }

  void GUI_Editor::clear()
  {
    GUI_ImGui::clear();
  }
}