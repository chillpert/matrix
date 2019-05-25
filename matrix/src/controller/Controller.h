#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "matrix/src/pch/stdafx.h"

namespace MX 
{
  class MX_API Controller 
  {
  public:
    inline static Controller &get() 
    {
      static Controller instance;
      return instance;
    }

    void handleKeyPressed(int keyCode);
    void handleKeyReleased(int keyCode);

    void handleMouseMoved(int x, int y);
    void handleMousePressed(int keyCode);
    void handleMouseReleased(int keyCode);
    void handleMouseScrolled(int x, int y);

    void handleCloseWindow();
    void handleResizeWindow(int width, int height);
    
    // toggle mouse hidden
    bool m_MouseHidden = 1;
  private:
    Controller() {}
    ~Controller() {}

    // last position of mouse
    int m_X;
    int m_Y;

    // last button pressed
    int m_KeyPressed;

    // last button released
    int m_KeyReleased;
  };
}

#ifdef MX_GLFW_ACTIVE

  // Keyboard
  #define MX_Q_KEY    GLFW_KEY_Q
  #define MX_W_KEY    GLFW_KEY_W
  #define MX_E_KEY    GLFW_KEY_E
  #define MX_R_KEY    GLFW_KEY_R
  #define MX_T_KEY    GLFW_KEY_T
  #define MX_Z_KEY    GLFW_KEY_Z
  #define MX_U_KEY    GLFW_KEY_U
  #define MX_I_KEY    GLFW_KEY_I
  #define MX_O_KEY    GLFW_KEY_O
  #define MX_P_KEY    GLFW_KEY_P
  #define MX_A_KEY    GLFW_KEY_A
  #define MX_S_KEY    GLFW_KEY_S
  #define MX_D_KEY    GLFW_KEY_D   
  #define MX_F_KEY    GLFW_KEY_F
  #define MX_G_KEY    GLFW_KEY_G
  #define MX_H_KEY    GLFW_KEY_H
  #define MX_J_KEY    GLFW_KEY_J
  #define MX_K_KEY    GLFW_KEY_K
  #define MX_L_KEY    GLFW_KEY_L
  #define MX_Y_KEY    GLFW_KEY_Y
  #define MX_X_KEY    GLFW_KEY_X
  #define MX_C_KEY    GLFW_KEY_C
  #define MX_V_KEY    GLFW_KEY_V
  #define MX_B_KEY    GLFW_KEY_B
  #define MX_N_KEY    GLFW_KEY_N
  #define MX_M_KEY    GLFW_KEY_M

  #define MX_ESCAPE_KEY       GLFW_KEY_ESCAPE
  #define MX_TAB_KEY          GLFW_KEY_TAB
  #define MX_CAPS_LOCK_KEY    GLFW_KEY_CAPS_LOCK
  #define MX_L_SHIFT_KEY      GLFW_KEY_LEFT_SHIFT
  #define MX_L_CTRL_KEY       GLFW_KEY_LEFT_CONTROL
  #define MX_L_ALT_KEY        GLFW_KEY_LEFT_ALT
  #define MX_SPACE_KEY        GLFW_KEY_SPACE
  #define MX_R_ALT_KEY        GLFW_KEY_RIGHT_ALT
  #define MX_R_CTRL_KEY       GLFW_KEY_RIGHT_CONTROL
  #define MX_R_SHIFT_KEY      GLFW_KEY_RIGHT_SHIFT
  #define MX_ENTER_KEY        GLFW_KEY_ENTER
  #define MX_BACKSPACE_KEY    GLFW_KEY_BACKSLASH

  #define MX_0_KEY    GLFW_KEY_0
  #define MX_1_KEY    GLFW_KEY_1
  #define MX_2_KEY    GLFW_KEY_2
  #define MX_3_KEY    GLFW_KEY_3
  #define MX_4_KEY    GLFW_KEY_4
  #define MX_5_KEY    GLFW_KEY_5
  #define MX_6_KEY    GLFW_KEY_6
  #define MX_7_KEY    GLFW_KEY_7
  #define MX_8_KEY    GLFW_KEY_8
  #define MX_9_KEY    GLFW_KEY_9
  #define MX_F1_KEY   GLFW_KEY_F1
  #define MX_F2_KEY   GLFW_KEY_F2
  #define MX_F3_KEY   GLFW_KEY_F3
  #define MX_F4_KEY   GLFW_KEY_F4
  #define MX_F5_KEY   GLFW_KEY_F5
  #define MX_F6_KEY   GLFW_KEY_F6
  #define MX_F7_KEY   GLFW_KEY_F7
  #define MX_F8_KEY   GLFW_KEY_F8
  #define MX_F9_KEY   GLFW_KEY_F9
  #define MX_F10_KEY  GLFW_KEY_F10
  #define MX_F11_KEY  GLFW_KEY_F11
  #define MX_F12_KEY  GLFW_KEY_F12

  // Mouse
  #define MX_LEFT_CLICK   GLFW_MOUSE_BUTTON_LEFT
  #define MX_RIGHT_CLICK  GLFW_MOUSE_BUTTON_RIGHT
  #define MX_MIDDLE_CLICK GLFW_MOUSE_BUTTON_MIDDLE
#elif MX_SDL2_ACTIVE

  // Keyboard
  #define MX_Q_KEY        SDLK_q
  #define MX_W_KEY        SDLK_w
  #define MX_E_KEY        SDLK_e
  #define MX_R_KEY        SDLK_r
  #define MX_T_KEY        SDLK_t   
  #define MX_Z_KEY        SDLK_z
  #define MX_U_KEY        SDLK_u
  #define MX_I_KEY        SDLK_i
  #define MX_O_KEY        SDLK_o
  #define MX_P_KEY        SDLK_p
  #define MX_A_KEY        SDLK_a
  #define MX_S_KEY        SDLK_s
  #define MX_D_KEY        SDLK_d
  #define MX_F_KEY        SDLK_f
  #define MX_G_KEY        SDLK_g
  #define MX_H_KEY        SDLK_h
  #define MX_J_KEY        SDLK_j
  #define MX_K_KEY        SDLK_k
  #define MX_L_KEY        SDLK_l
  #define MX_Y_KEY        SDLK_y
  #define MX_X_KEY        SDLK_x
  #define MX_C_KEY        SDLK_c
  #define MX_V_KEY        SDLK_v
  #define MX_B_KEY        SDLK_b
  #define MX_N_KEY        SDLK_n
  #define MX_M_KEY        SDLK_m

  #define MX_ESCAPE_KEY       SDLK_ESCAPE     
  #define MX_TAB_KEY          SDLK_TAB
  #define MX_CAPS_LOCK_KEY    SDLK_CAPSLOCK
  #define MX_L_SHIFT_KEY      SDLK_LSHIFT
  #define MX_L_CTRL_KEY       SDLK_LCTRL
  #define MX_L_ALT_KEY        SDLK_LALT
  #define MX_SPACE_KEY        SDLK_SPACE
  #define MX_R_ALT_KEY        SDLK_RALT
  #define MX_R_CTRL_KEY       SDLK_RCTRL
  #define MX_R_SHIFT_KEY      SDLK_RSHIFT
  #define MX_ENTER_KEY        SDLK_RETURN
  #define MX_BACKSPACE_KEY    SDLK_BACKSPACE

  #define MX_0_KEY    SDLK_0    
  #define MX_1_KEY    SDLK_1   
  #define MX_2_KEY    SDLK_2
  #define MX_3_KEY    SDLK_3
  #define MX_4_KEY    SDLK_4
  #define MX_5_KEY    SDLK_5
  #define MX_6_KEY    SDLK_6
  #define MX_7_KEY    SDLK_7
  #define MX_8_KEY    SDLK_8
  #define MX_9_KEY    SDLK_9
  #define MX_F1_KEY   SDLK_F1 
  #define MX_F2_KEY   SDLK_F2 
  #define MX_F3_KEY   SDLK_F3 
  #define MX_F4_KEY   SDLK_F4 
  #define MX_F5_KEY   SDLK_F5 
  #define MX_F6_KEY   SDLK_F6 
  #define MX_F7_KEY   SDLK_F7 
  #define MX_F8_KEY   SDLK_F8 
  #define MX_F9_KEY   SDLK_F9 
  #define MX_F10_KEY  SDLK_F10
  #define MX_F11_KEY  SDLK_F11
  #define MX_F12_KEY  SDLK_F12

  // Mouse
  #define MX_LEFT_CLICK   SDL_BUTTON_LEFT
  #define MX_RIGHT_CLICK  SDL_BUTTON_RIGHT
  #define MX_MIDDLE_CLICK SDL_BUTTON_MIDDLE
#endif

#define PRINT_KEY(x) #x

#endif // CONTROLLER_H