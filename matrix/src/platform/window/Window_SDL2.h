#ifndef Window_SDL2_H
#define Window_SDL2_H

#include "matrix/src/platform/window/Window.h"

namespace MX
{
  class Window_SDL2 : public Window
  {
  public:
  	MX_API Window_SDL2() = default;
    MX_API ~Window_SDL2() = default;

    MX_API Window_SDL2(const Window_SDL2&) = default;
    MX_API Window_SDL2 &operator=(const Window_SDL2&) = default;

    MX_API void update() override;
    MX_API void render() override;
    MX_API bool initialize() override;

    MX_API void close() override;
    MX_API void controllerCallback() const override;

    MX_API void setTitle(const std::string &title) override;
    MX_API void resize(int width, int height) override;
    
    MX_API Window_SDL2 *getWindow() override { return this; }
  
    SDL_GLContext m_Context;
    SDL_Window *m_Window = NULL;
  };
}

#endif // Window_SDL2_H