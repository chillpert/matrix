#ifndef INPUTMAP_H
#define INPUTMAP_H

#include "matrix/src/Application.h"
#include "matrix/src/Camera.h"

namespace Matrix {

    extern float speed;
}

#define MX_UNKOWN_PRESSED    
#define MX_W_PRESSED            Camera::get().processKeyboard(FORWARDS, speed);       
#define MX_A_PRESSED            Camera::get().processKeyboard(FORWARDS, speed);
#define MX_S_PRESSED            Camera::get().processKeyboard(FORWARDS, speed);
#define MX_D_PRESSED            Camera::get().processKeyboard(FORWARDS, speed);
#define MX_C_PRESSED            Camera::get().processKeyboard(FORWARDS, speed);
#define MX_SPACE_PRESSED        Camera::get().processKeyboard(FORWARDS, speed);
#define MX_ESCAPE_PRESSED       Application::get().stop();
#define MX_L_SHIFT_PRESSED      speed = 5.0f;

#define MX_UNKOWN_RELEASED
#define MX_W_RELEASED
#define MX_A_RELEASED
#define MX_S_RELEASED
#define MX_D_RELEASED
#define MX_C_RELEASED
#define MX_SPACE_RELEASED
#define MX_ESCAPE_RELEASED
#define MX_L_SHIFT_RELEASED     speed = 1.0f;

#endif // INPUTMAP_H