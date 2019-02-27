#ifndef WINDOWSDL2_H
#define WINDOWSDL2_H

#include "matrix/src/platform/window/Window.h"

#ifdef MX_SDL2_ACTIVE

namespace Matrix {

    class WindowSDL2 : public Window {
    public:
    	MATRIX_API WindowSDL2() {}
        MATRIX_API ~WindowSDL2() {}

        MATRIX_API void update() const override; 
        MATRIX_API void render() const override; 

        MATRIX_API bool createContext() override;
        MATRIX_API void resize() const override;
        MATRIX_API void close() const override;

        MATRIX_API void controllerCallback() override;

        MATRIX_API inline SDL_Window* getWindow() { return m_Window; } 
        MATRIX_API inline SDL_GLContext &getSurface() { return m_Context; }
    private:
        SDL_Window* m_Window = NULL;
        SDL_GLContext m_Context;
    };
}

#endif

#endif // WINDOWSDL2_H