#include "matrix/src/controller/Controller.h"
#include "matrix/src/controller/InputMap.h"
#include "matrix/src/Application.h"

namespace MX 
{
  
  void Controller::handleKeyPressed(int keyCode) 
  {
    m_KeyPressed = keyCode;
    switch (keyCode) 
    {
      case MX_Q_KEY:
        MX_Q_PRESSED; break;
      case MX_W_KEY:
        MX_W_PRESSED; break;
      case MX_E_KEY:
        MX_E_PRESSED; break;
      case MX_R_KEY:
        MX_R_PRESSED; break;
      case MX_T_KEY:
        MX_T_PRESSED; break;
      case MX_Z_KEY:
        MX_Z_PRESSED; break;
      case MX_U_KEY:
        MX_U_PRESSED; break;
      case MX_I_KEY:
        MX_I_PRESSED; break;
      case MX_O_KEY:
        MX_O_PRESSED; break;
      case MX_P_KEY:
        MX_P_PRESSED; break;
      case MX_A_KEY:
        MX_A_PRESSED; break;
      case MX_S_KEY:
        MX_S_PRESSED; break;
      case MX_D_KEY:
        MX_D_PRESSED; break;
      case MX_F_KEY:
        MX_F_PRESSED; break;
      case MX_G_KEY:
        MX_G_PRESSED; break;
      case MX_H_KEY:
        MX_H_PRESSED; break;
      case MX_J_KEY:
        MX_J_PRESSED; break;
      case MX_K_KEY:
        MX_K_PRESSED; break;
      case MX_L_KEY:
        MX_L_PRESSED; break;
      case MX_Y_KEY:
        MX_Y_PRESSED; break;
      case MX_X_KEY:
        MX_X_PRESSED; break;
      case MX_C_KEY:
        MX_C_PRESSED; break;
      case MX_V_KEY:
        MX_V_PRESSED; break;
      case MX_B_KEY:
        MX_B_PRESSED; break;
      case MX_N_KEY:
        MX_N_PRESSED; break;
      case MX_M_KEY:
        MX_M_PRESSED; break;
      case MX_ESCAPE_KEY:
        MX_ESCAPE_PRESSED; break;
      case MX_TAB_KEY:
        MX_TAB_PRESSED; break;
      case MX_CAPS_LOCK_KEY:
        MX_CAPS_LOCK_PRESSED; break;
      case MX_L_SHIFT_KEY:
        MX_L_SHIFT_PRESSED; break;
      case MX_L_CTRL_KEY:
        MX_L_CTRL_PRESSED; break;
      case MX_L_ALT_KEY:
        MX_L_ALT_PRESSED; break;
      case MX_SPACE_KEY:
        MX_SPACE_PRESSED; break;
      case MX_R_ALT_KEY:
        MX_R_ALT_PRESSED; break;
      case MX_R_CTRL_KEY:
        MX_R_CTRL_PRESSED; break;
      case MX_R_SHIFT_KEY:
        MX_R_SHIFT_PRESSED; break;
      case MX_ENTER_KEY:
        MX_ENTER_PRESSED; break;
      case MX_BACKSPACE_KEY:
        MX_BACKSPACE_PRESSED; break;
      case MX_0_KEY:
        MX_0_PRESSED; break;
      case MX_1_KEY:
        MX_1_PRESSED; break;
      case MX_2_KEY:
        MX_2_PRESSED; break;
      case MX_3_KEY:
        MX_3_PRESSED; break;
      case MX_4_KEY:
        MX_4_PRESSED; break;
      case MX_5_KEY:
        MX_5_PRESSED; break;
      case MX_6_KEY:
        MX_6_PRESSED; break;
      case MX_7_KEY:
        MX_7_PRESSED; break;
      case MX_8_KEY:
        MX_8_PRESSED; break;
      case MX_9_KEY:
        MX_9_PRESSED; break;
      case MX_F1_KEY:
        MX_F1_PRESSED; break;
      case MX_F2_KEY:
        MX_F2_PRESSED; break;
      case MX_F3_KEY:
        MX_F3_PRESSED; break;
      case MX_F4_KEY:
        MX_F4_PRESSED; break;
      case MX_F5_KEY:
        MX_F5_PRESSED; break;
      case MX_F6_KEY:
        MX_F6_PRESSED; break;
      case MX_F7_KEY:
        MX_F7_PRESSED; break;
      case MX_F8_KEY:
        MX_F8_PRESSED; break;
      case MX_F9_KEY:
        MX_F9_PRESSED; break;
      case MX_F10_KEY:
        MX_F10_PRESSED; break;
      case MX_F11_KEY:
        MX_F11_PRESSED; break;
      case MX_F12_KEY:
        MX_F12_PRESSED; break;
      default:
        MX_WARN("MX: Key pressed: " + std::to_string(keyCode) + " is not programmed"); break;            
    }
  }

  void Controller::handleKeyReleased(int keyCode) 
  {
    m_KeyReleased = keyCode;
    switch (keyCode) {
      case MX_Q_KEY:
        MX_Q_RELEASED; break;
      case MX_W_KEY:
        MX_W_RELEASED; break;
      case MX_E_KEY:
        MX_E_RELEASED; break;
      case MX_R_KEY:
        MX_R_RELEASED; break;
      case MX_T_KEY:
        MX_T_RELEASED; break;
      case MX_Z_KEY:
        MX_Z_RELEASED; break;
      case MX_U_KEY:
        MX_U_RELEASED; break;
      case MX_I_KEY:
        MX_I_RELEASED; break;
      case MX_O_KEY:
        MX_O_RELEASED; break;
      case MX_P_KEY:
        MX_P_RELEASED; break;
      case MX_A_KEY:
        MX_A_RELEASED; break;
      case MX_S_KEY:
        MX_S_RELEASED; break;
      case MX_D_KEY:
        MX_D_RELEASED; break;
      case MX_F_KEY:
        MX_F_RELEASED; break;
      case MX_G_KEY:
        MX_G_RELEASED; break;
      case MX_H_KEY:
        MX_H_RELEASED; break;
      case MX_J_KEY:
        MX_J_RELEASED; break;
      case MX_K_KEY:
        MX_K_RELEASED; break;
      case MX_L_KEY:
        MX_L_RELEASED; break;
      case MX_Y_KEY:
        MX_Y_RELEASED; break;
      case MX_X_KEY:
        MX_X_RELEASED; break;
      case MX_C_KEY:
        MX_C_RELEASED; break;
      case MX_V_KEY:
        MX_V_RELEASED; break;
      case MX_B_KEY:
        MX_B_RELEASED; break;
      case MX_N_KEY:
        MX_N_RELEASED; break;
      case MX_M_KEY:
        MX_M_RELEASED; break;
      case MX_ESCAPE_KEY:
        MX_ESCAPE_RELEASED; break;
      case MX_TAB_KEY:
        MX_TAB_RELEASED; break;
      case MX_CAPS_LOCK_KEY:
        MX_CAPS_LOCK_RELEASED; break;
      case MX_L_SHIFT_KEY:
        MX_L_SHIFT_RELEASED; break;
      case MX_L_CTRL_KEY:
        MX_L_CTRL_RELEASED; break;
      case MX_L_ALT_KEY:
        MX_L_ALT_RELEASED; break;
      case MX_SPACE_KEY:
        MX_SPACE_RELEASED; break;
      case MX_R_ALT_KEY:
        MX_R_ALT_RELEASED; break;
      case MX_R_CTRL_KEY:
        MX_R_CTRL_RELEASED; break;
      case MX_R_SHIFT_KEY:
        MX_R_SHIFT_RELEASED; break;
      case MX_ENTER_KEY:
        MX_ENTER_RELEASED; break;
      case MX_BACKSPACE_KEY:
        MX_BACKSPACE_RELEASED; break;
      case MX_0_KEY:
        MX_0_RELEASED; break;
      case MX_1_KEY:
        MX_1_RELEASED; break;
      case MX_2_KEY:
        MX_2_RELEASED; break;
      case MX_3_KEY:
        MX_3_RELEASED; break;
      case MX_4_KEY:
        MX_4_RELEASED; break;
      case MX_5_KEY:
        MX_5_RELEASED; break;
      case MX_6_KEY:
        MX_6_RELEASED; break;
      case MX_7_KEY:
        MX_7_RELEASED; break;
      case MX_8_KEY:
        MX_8_RELEASED; break;
      case MX_9_KEY:
        MX_9_RELEASED; break;
      case MX_F1_KEY:
        MX_F1_RELEASED; break;
      case MX_F2_KEY:
        MX_F2_RELEASED; break;
      case MX_F3_KEY:
        MX_F3_RELEASED; break;
      case MX_F4_KEY:
        MX_F4_RELEASED; break;
      case MX_F5_KEY:
        MX_F5_RELEASED; break;
      case MX_F6_KEY:
        MX_F6_RELEASED; break;
      case MX_F7_KEY:
        MX_F7_RELEASED; break;
      case MX_F8_KEY:
        MX_F8_RELEASED; break;
      case MX_F9_KEY:
        MX_F9_RELEASED; break;
      case MX_F10_KEY:
        MX_F10_RELEASED; break;
      case MX_F11_KEY:
        MX_F11_RELEASED; break;
      case MX_F12_KEY:
        MX_F12_RELEASED; break;
      default:
        MX_WARN("MX: Key released: " + std::to_string(keyCode) + " is not programmed"); break;            
    }
  }
    

  void Controller::handleMouseMoved(int x, int y)
  {
    m_X = x;
    m_Y = y;
    //MX_MOUSE_MOVED(float(m_X), float(m_Y));
  }

  void Controller::handleMousePressed(int keyCode)
  {
    switch (keyCode) {
      case MX_LEFT_CLICK:
        MX_LEFT_PRESSED; break;
      case MX_RIGHT_CLICK:
        MX_RIGHT_PRESSED; break;
      case MX_MIDDLE_CLICK:
        MX_MIDDLE_PRESSED; break;
      default:
        MX_WARN("MX: Key pressed: " + std::to_string(keyCode) + " is not programmed"); break;
    }
  }

  void Controller::handleMouseReleased(int keyCode)
  {
    switch (keyCode) {
      case MX_LEFT_CLICK:
        MX_LEFT_RELEASED; break;
      case MX_RIGHT_CLICK:
        MX_RIGHT_RELEASED; break;
      case MX_MIDDLE_CLICK:
        MX_RIGHT_RELEASED; break;
      default:
        MX_WARN("MX: Key released: " + std::to_string(keyCode) + " is not programmed"); break;
    }
  }

  void Controller::handleMouseScrolled(int x, int y)
  {
    switch (y) 
    {
      case  1:
        MX_SCROLL_UP; break;
      case -1:
        MX_SCROLL_DOWN; break;
      default:
        MX_WARN("MX: Scroll direction is not programmed"); break;
    }
  }

  void Controller::handleCloseWindow()
  {
    Application::get().m_Running = 0;
  }

  void Controller::handleResizeWindow(int width, int height)
  {
    Application::get().m_Window->m_Props.m_Width = width;
    Application::get().m_Window->m_Props.m_Height = height;
  }
}