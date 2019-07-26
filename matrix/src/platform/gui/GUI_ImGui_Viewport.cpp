#include <GUI_ImGui.h>
#include <Application.h>
#include <World.h>

namespace MX
{
  static bool first_run = 1;
  static bool dockspace_p_open = 1;
  static int current_frame = 0;

  void renderDockSpace()
  {
  #ifdef MX_IMGUI_ACTIVE
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
      ImGuiViewport* viewport = ImGui::GetMainViewport();
      auto window_props = Application::get().m_Window->m_Props;
      ImGui::SetNextWindowPos(viewport->Pos);
      ImGui::SetNextWindowSize(viewport->Size);
      ImGui::SetNextWindowViewport(viewport->ID);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
      window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
      window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
      window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockspace_p_open, window_flags);
    ImGui::PopStyleVar();

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
      ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
      ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (opt_fullscreen)
      ImGui::PopStyleVar(2);

    ImGui::End();
  #endif
  }

  void renderViewport()
  {
  #ifdef MX_IMGUI_ACTIVE
    static ImGuiWindowFlags window_flags = 0;
    static bool no_titlebar = 0;
    static bool no_scrollbar = 0;
    static bool no_menu = 1;
    static bool no_move = 0;
    static bool no_resize = 0;
    static bool no_collapse = 1;
    static bool no_nav = 0;
    static bool no_background = 1;
    static bool no_bring_to_front = 0;
    static bool no_autoresize = 0;

    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus; 
    if (no_autoresize)      window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

    static int first_iteration = 1;
    static ImTextureID my_tex_id;
    static float my_tex_w;
    static float my_tex_h;

    current_frame = Application::get().m_Window->m_Props.m_Frames;

    if (ImGui::Begin("View Port", &p_open_viewport, window_flags))
    {
      std::string fps_message = std::to_string(current_frame) + " FPS";
      ImGui::Text(fps_message.c_str());

      Window::WindowProps::ViewPort *app_viewport = &Application::get().m_Window->m_Props.m_Viewport;

      if (first_iteration)
      {
        std::unique_ptr<Texture> play_button(std::make_unique<MX_TEXTURE>("diffuse/elon.jpg"));
        auto derived_tex_ptr = static_cast<MX_TEXTURE*>(play_button.get());
        
        play_button->initialize();
        my_tex_id = (void*)derived_tex_ptr->getID();
        my_tex_w = derived_tex_ptr->m_Stb.width;
        my_tex_h = derived_tex_ptr->m_Stb.height;
        first_iteration = 0;
      }

      ImGui::SameLine();
      if (ImGui::ImageButton(
        my_tex_id,
        ImVec2(16.0f, 16.0f),
        ImVec2(-1, -1), ImVec2(16.0f / my_tex_w, 16.0f / my_tex_h),
        3,
        ImVec4(0.0f, 0.0f, 0.0f, 1.0f))
      )
        current_scenegraph->is_paused = !current_scenegraph->is_paused;

      static int menubar_offset = 19;

      if (!first_run)
      {
        ImGui::SetWindowPos(ImVec2(0, menubar_offset));
        ImGui::SetWindowSize(ImVec2(
          app_viewport->m_Viewport_max_x,
          app_viewport->m_Viewport_max_y - menubar_offset
        ));
        first_run = 0;
      }

      // comments are values at start up with window resolution of 1200, 600
      auto window_size = ImGui::GetWindowSize(); // 853, 581
      auto window_pos = ImGui::GetWindowPos(); // 0, 19

      app_viewport->m_Viewport_min_x = window_pos.x; // 0
      app_viewport->m_Viewport_min_y = window_size.y + window_pos.y; // 19

      app_viewport->m_Viewport_max_x = window_size.x; // 853
      app_viewport->m_Viewport_max_y = window_size.y; // 581

      if (Application::get().m_API->m_framebuffer.m_initialized)
      {
        ImVec2 pos = ImGui::GetCursorScreenPos();
/*
        ImGui::GetWindowDrawList()->AddImage(
          (void*)Application::get().m_API->m_framebuffer.m_fbo,
          ImVec2(
            ImGui::GetItemRectMin().x + pos.x,
            ImGui::GetItemRectMin().y + pos.y
          ),
          ImVec2(pos.x + 1400 / 2, pos.y + 800 / 2),
          ImVec2(0, 1), ImVec2(1, 0)
        );
*/

/*
        ImGui::GetWindowDrawList()->AddImage(
          (void*)Application::get().m_API->m_framebuffer.m_fbo,
          ImVec2(ImGui::GetCursorScreenPos()),
          ImVec2(ImGui::GetCursorScreenPos().x + 900/2, 
          ImGui::GetCursorScreenPos().y + 500/2),
          ImVec2(0, 1), ImVec2(1, 0)
        );
*/
      }
    }
    ImGui::End();

    if (ImGui::Begin("test"))
    {
      ImGui::GetWindowDrawList()->AddImage(
          (void*)Application::get().m_API->m_framebuffer.m_fbo,
          ImVec2(ImGui::GetCursorScreenPos()),
          ImVec2(ImGui::GetCursorScreenPos().x + 900/2, 
          ImGui::GetCursorScreenPos().y + 500/2),
          ImVec2(0, 1), ImVec2(1, 0)
        );
    }
    ImGui::End();

  #endif
  }

  void renderPerformanceMonitor()
  {
  #ifdef MX_IMGUI_ACTIVE
    static bool no_titlebar = 0;
    static bool no_scrollbar = 0;
    static bool no_menu = 0;
    static bool no_move = 0;
    static bool no_resize = 0;
    static bool no_collapse = 1;
    static bool no_nav = 0;
    static bool no_background = 0;
    static bool no_bring_to_front = 0;

    static ImGuiWindowFlags window_flags = 0;

    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    if (ImGui::Begin("Performance Monitor", &p_open_performance_monitor, window_flags))
    {
      if (!p_open_performance_monitor)
        performance_monitor_enabled = 0;

      static bool is_running = 1;
      static bool is_recording = 0;

      static float fps_avg;
      static int max_fps = 0;
      static std::vector<float> frames;

      if (is_running)
        frames.push_back(static_cast<float>(current_frame));

      if (current_frame > max_fps)
        max_fps = current_frame;

      for (float it : frames)
        fps_avg += it;

      fps_avg /= frames.size();

      std::string fps_avg_message = "avg " + std::to_string(fps_avg);

      ImGui::PlotLines("Frame Time", frames.data(), frames.size(), 0, fps_avg_message.c_str(), 0.0f, static_cast<int>(max_fps) * 2.0f, ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight() - 65.0f)); // 37.0f so that no scroll bar will appear

      if (ImGui::BeginMenuBar())
      {
        if (ImGui::MenuItem("Reset", "", true, is_running && !is_recording))
          frames.clear();

        if (is_running)
        {
          if (ImGui::MenuItem("Pause", "", true, !is_recording))
            is_running = 0;
        }
        else
        {
          if (ImGui::MenuItem("Continue", "", true, !is_recording))
            is_running = 1;
        }

        // write to performance_report.txt
        if (is_recording)
        {
          if (ImGui::MenuItem("Stop", "", true, is_running))
            is_recording = 0;
        }
        else
        {
          if (ImGui::MenuItem("Record", "", true, is_running))
            is_recording = 1;
        }

        ImGui::EndMenuBar();
      }

      if (frames.size() > 20000)
        frames.clear();
    }
    ImGui::End();
  #endif
  }
}