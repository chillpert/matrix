#ifndef CONTROLLER_H
#define CONTROLLER_H

#ifdef MX_GLFW_ACTIVE
    // Keyboard
    #define MX_W_KEY        GLFW_KEY_W
    #define MX_A_KEY        GLFW_KEY_A 
    #define MX_S_KEY        GLFW_KEY_S 
    #define MX_D_KEY        GLFW_KEY_D 
    #define MX_C_KEY        GLFW_KEY_C 
    #define MX_SPACE_KEY    GLFW_KEY_SPACE
    #define MX_ESCAPE_KEY   GLFW_KEY_ESCAPE
    #define MX_L_SHIFT_KEY  GLFW_KEY_LEFT_SHIFT
    // Mouse
    #define MX_LEFT_CLICK   GLFW_MOUSE_BUTTON_LEFT
    #define MX_RIGHT_CLICK  GLFW_MOUSE_BUTTON_RIGHT
    #define MX_MIDDLE_CLICK GLFW_MOUSE_BUTTON_MIDDLE
#elif MX_SDL2_ACTIVE
    // Keyboard
    #define MX_W_KEY        SDLK_w
    #define MX_A_KEY        SDLK_a
    #define MX_S_KEY        SDLK_s
    #define MX_D_KEY        SDLK_d
    #define MX_C_KEY        SDLK_c
    #define MX_SPACE_KEY    SDLK_SPACE
    #define MX_ESCAPE_KEY   SDLK_ESCAPE
    #define MX_L_SHIFT_KEY  SDLK_LSHIFT
    // Mouse
    #define MX_LEFT_CLICK   SDL_BUTTON_LEFT
    #define MX_RIGHT_CLICK  SDL_BUTTON_RIGHT
    #define MX_MIDDLE_CLICK SDL_BUTTON_MIDDLE
#endif

#define PRINT_KEY(x) #x

#include "matrix/src/pch/stdafx.h"

namespace MX {

    class MX_API Controller {
    public:
        ~Controller() {}
        
        inline static Controller& get() {
            static Controller instance;
            return instance;
        }

        void handleKeyPressed(int keyCode);
        void handleKeyReleased(int keyCode);

        void handleMouseMoved(int x, int y);
        void handleMousePressed(int keyCode);
        void handleMouseReleased(int keyCode);
        void handleMouseScrolled(int x, int y);
    protected:
        Controller() {}
        // last position of mouse
        int m_X;
        int m_Y;
        // last button pressed
        int m_KeyPressed;
        // last button released
        int m_KeyReleased;
    };
}

#endif // CONTROLLER_H