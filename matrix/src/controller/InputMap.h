#ifndef INPUTMAP_H
#define INPUTMAP_H

#include <Controller.h>
#include <World.h>
#include <Camera.h>
#include <Application.h>

namespace MX 
{
  extern float speed;

  extern bool key_w;
  extern bool key_a;
  extern bool key_s;
  extern bool key_d;
  extern bool key_c;
  extern bool key_space;

  void disable_all_keys();
  
  // keyboard (pressed)
  #define MX_Q_PRESSED
  #define MX_W_PRESSED key_w = 1;
  #define MX_E_PRESSED 
  #define MX_R_PRESSED
  #define MX_T_PRESSED
  #define MX_Z_PRESSED
  #define MX_U_PRESSED
  #define MX_I_PRESSED
  #define MX_O_PRESSED
  #define MX_P_PRESSED
  #define MX_A_PRESSED key_a = 1;
  #define MX_S_PRESSED key_s = 1;
  #define MX_D_PRESSED key_d = 1;
  #define MX_F_PRESSED
  #define MX_G_PRESSED
  #define MX_H_PRESSED
  #define MX_J_PRESSED
  #define MX_K_PRESSED
  #define MX_L_PRESSED
  #define MX_Y_PRESSED
  #define MX_X_PRESSED
  #define MX_C_PRESSED key_c = 1;
  #define MX_V_PRESSED
  #define MX_B_PRESSED
  #define MX_N_PRESSED
  #define MX_M_PRESSED

  #define MX_ESCAPE_PRESSED Controller::get().handleCloseWindow();
  #define MX_TAB_PRESSED
  #define MX_CAPS_LOCK_PRESSED
  #define MX_L_SHIFT_PRESSED
  #define MX_L_CTRL_PRESSED
  #define MX_L_ALT_PRESSED
  #define MX_SPACE_PRESSED key_space = 1;
  #define MX_R_ALT_PRESSED   
  #define MX_R_CTRL_PRESSED   
  #define MX_R_SHIFT_PRESSED  
  #define MX_ENTER_PRESSED    
  #define MX_BACKSPACE_PRESSED
  #define MX_0_PRESSED   
  #define MX_1_PRESSED   
  #define MX_2_PRESSED   
  #define MX_3_PRESSED   
  #define MX_4_PRESSED   
  #define MX_5_PRESSED   
  #define MX_6_PRESSED   
  #define MX_7_PRESSED   
  #define MX_8_PRESSED   
  #define MX_9_PRESSED   
  #define MX_F1_PRESSED  
  #define MX_F2_PRESSED  
  #define MX_F3_PRESSED  
  #define MX_F4_PRESSED  
  #define MX_F5_PRESSED  
  #define MX_F6_PRESSED  
  #define MX_F7_PRESSED  
  #define MX_F8_PRESSED  
  #define MX_F9_PRESSED  
  #define MX_F10_PRESSED 
  #define MX_F11_PRESSED 
  #define MX_F12_PRESSED 

  // keyboard (released)
  #define MX_Q_RELEASED
  #define MX_W_RELEASED key_w = 0;
  #define MX_E_RELEASED
  #define MX_R_RELEASED
  #define MX_T_RELEASED
  #define MX_Z_RELEASED
  #define MX_U_RELEASED
  #define MX_I_RELEASED
  #define MX_O_RELEASED
  #define MX_P_RELEASED
  #define MX_A_RELEASED key_a = 0;
  #define MX_S_RELEASED key_s = 0;
  #define MX_D_RELEASED key_d = 0;
  #define MX_F_RELEASED
  #define MX_G_RELEASED
  #define MX_H_RELEASED
  #define MX_J_RELEASED
  #define MX_K_RELEASED
  #define MX_L_RELEASED
  #define MX_Y_RELEASED
  #define MX_X_RELEASED
  #define MX_C_RELEASED key_c = 0;
  #define MX_V_RELEASED
  #define MX_B_RELEASED
  #define MX_N_RELEASED
  #define MX_M_RELEASED

  #define MX_ESCAPE_RELEASED
  #define MX_TAB_RELEASED      
  #define MX_CAPS_LOCK_RELEASED
  #define MX_L_SHIFT_RELEASED
  #define MX_L_CTRL_RELEASED
  #define MX_L_ALT_RELEASED
  #define MX_SPACE_RELEASED key_space = 0;
  #define MX_R_ALT_RELEASED
  #define MX_R_CTRL_RELEASED
  #define MX_R_SHIFT_RELEASED
  #define MX_ENTER_RELEASED
  #define MX_BACKSPACE_RELEASED
  #define MX_0_RELEASED   
  #define MX_1_RELEASED   
  #define MX_2_RELEASED   
  #define MX_3_RELEASED   
  #define MX_4_RELEASED   
  #define MX_5_RELEASED   
  #define MX_6_RELEASED   
  #define MX_7_RELEASED   
  #define MX_8_RELEASED   
  #define MX_9_RELEASED   
  #define MX_F1_RELEASED  
  #define MX_F2_RELEASED  
  #define MX_F3_RELEASED  
  #define MX_F4_RELEASED  
  #define MX_F5_RELEASED  
  #define MX_F6_RELEASED  
  #define MX_F7_RELEASED  
  #define MX_F8_RELEASED  
  #define MX_F9_RELEASED  
  #define MX_F10_RELEASED 
  #define MX_F11_RELEASED 
  #define MX_F12_RELEASED 

  // mouse (pressed)
  #define MX_LEFT_PRESSED     
  #define MX_RIGHT_PRESSED Controller::get().m_MouseHidden = 1;\
                           Controller::get().m_FirstMouse = 1;\
                           disable_all_keys();
  #define MX_MIDDLE_PRESSED 
  #define MX_SCROLL_UP

  // mouse (released)
  #define MX_LEFT_RELEASED        
  #define MX_RIGHT_RELEASED Controller::get().m_MouseHidden = 0;\
                            Controller::get().m_FirstMouse = 1;\
                            disable_all_keys();
  #define MX_MIDDLE_RELEASED
  #define MX_SCROLL_DOWN

  // mouse (moved)
  #define MX_MOUSE_MOVED(x, y)  MX_WORLD.m_ActiveScene->m_Cam.processMouse(x,y);

}

#endif // INPUTMAP_H