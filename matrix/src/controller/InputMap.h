#ifndef INPUTMAP_H
#define INPUTMAP_H

#include "matrix/src/Application.h"
#include "matrix/src/Camera.h"

namespace MX {

    extern float speed;
}

// keyboard (pressed)  
#define MX_W_PRESSED            Camera::get().processKeyboard(FORWARDS, speed);       
#define MX_A_PRESSED            Camera::get().processKeyboard(FORWARDS, speed);
#define MX_S_PRESSED            Camera::get().processKeyboard(FORWARDS, speed);
#define MX_D_PRESSED            Camera::get().processKeyboard(FORWARDS, speed);
#define MX_C_PRESSED            Camera::get().processKeyboard(FORWARDS, speed);
#define MX_SPACE_PRESSED        Camera::get().processKeyboard(FORWARDS, speed);
#define MX_ESCAPE_PRESSED       Application::get().stop();
#define MX_L_SHIFT_PRESSED      speed = 5.0f;
// mouse (pressed)
#define MX_LEFT_PRESSED          
#define MX_RIGHT_PRESSED
#define MX_MIDDLE_PRESSED
#define MX_SCROLL_UP

// keyboard (released)
#define MX_W_RELEASED
#define MX_A_RELEASED
#define MX_S_RELEASED
#define MX_D_RELEASED
#define MX_C_RELEASED
#define MX_SPACE_RELEASED
#define MX_ESCAPE_RELEASED
#define MX_L_SHIFT_RELEASED     speed = 1.0f;
// mouse (released)
#define MX_LEFT_RELEASED        
#define MX_RIGHT_RELEASED
#define MX_MIDDLE_RELEASED
#define MX_SCROLL_DOWN

#endif // INPUTMAP_H