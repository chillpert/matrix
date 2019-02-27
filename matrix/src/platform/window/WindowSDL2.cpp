#include "matrix/src/platform/window/WindowSDL2.h"
#include "matrix/src/event/KeyboardEvent.h"
#include "matrix/src/event/MouseEvent.h"

#ifdef MX_SDL2_ACTIVE

namespace Matrix {

    static std::string SDL_ErrorMessage;

    bool WindowSDL2::createContext() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            SDL_ErrorMessage = SDL_GetError();
            MX_FATAL("SDL2 context: " + SDL_ErrorMessage);
            return 0;
        } else {
            MX_SUCCESS("SDL2 context");

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); 
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
            SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

            m_Window = SDL_CreateWindow(m_Props.m_Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                        m_Props.m_Width, m_Props.m_Height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
            if (m_Window == NULL) {
                SDL_ErrorMessage = SDL_GetError();
                MX_FATAL("SDL2 window: " + SDL_ErrorMessage);
                return 0;
            } else {
                MX_SUCCESS("SDL2 window");

                m_Context = SDL_GL_CreateContext(m_Window);
                if (m_Context == NULL) {
                    SDL_ErrorMessage = SDL_GetError();
                    MX_FATAL("SDL2 GL context: " + SDL_ErrorMessage);
                } else {
                    MX_SUCCESS("SDL2 GL context");
                    return 1;
                }
            }
        }
        return 0;
    }

    void WindowSDL2::update() const {
        
    }

    void WindowSDL2::render() const {
        SDL_SetWindowTitle(m_Window, m_Props.m_Title.c_str());
        SDL_GL_SwapWindow(m_Window);
    }

    void WindowSDL2::resize() const {

    }

    void WindowSDL2::close() const {
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
    }

    void WindowSDL2::controllerCallback() {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_KEYDOWN) {
                KeyboardButtonPressed event(event.key.keysym.sym);
                event.handle();
                LOGEVENT;
            }
            if (event.type == SDL_KEYUP) {
                KeyboardButtonReleased event(event.key.keysym.sym);
                event.handle();
                LOGEVENT;
            }
            if (event.type == SDL_MOUSEMOTION) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                MouseMoved event(x, y);
                event.handle();
                LOGEVENT;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) { 
                MouseButtonPressed event(event.button.button);
                event.handle();
                LOGEVENT;
            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                MouseButtonReleased event(event.button.button);
                event.handle();
                LOGEVENT;
            }
        }   
    }
}

#endif