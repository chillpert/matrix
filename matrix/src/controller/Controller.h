#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdafx.h>

namespace MX 
{
  class MX_API Controller 
  {
  public:
    static Controller &get() 
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
    bool m_MouseHidden = 0;

    bool m_FirstMouse = 1;

    // last position of mouse
    int m_X;
    int m_Y;

    // last button pressed
    int m_KeyPressed;

    // last button released
    int m_KeyReleased;
    
  private:
    Controller() {}
    ~Controller() {}
  };
}

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

#define PRINT_KEY(x) #x

#endif // CONTROLLER_H