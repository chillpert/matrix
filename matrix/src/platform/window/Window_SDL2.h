#ifndef Window_SDL2_H
#define Window_SDL2_H

#include "matrix/src/platform/window/Window.h"

#ifdef MX_SDL2_ACTIVE

namespace MX
{
  class Window_SDL2 : public Window
  {
  public:
  	MX_API static Window_SDL2 &get()
    {
      static Window_SDL2 instance;
      return instance;
    }

    MX_API void update() const override; 
    MX_API void render() const override; 
    MX_API bool createContext() override;

    MX_API void close() const override;
    MX_API void controllerCallback() override;

    MX_API void setTitle() override;
    MX_API void resize() override;
    
    MX_API inline SDL_Window* getWindow() { return m_Window; } 
    MX_API inline SDL_GLContext& getContext() { return m_Context; }
  private:
    MX_API Window_SDL2() {}
    MX_API ~Window_SDL2() {}

    SDL_Window* m_Window = NULL;
    SDL_GLContext m_Context;
  };
}

#endif

#endif // Window_SDL2_H