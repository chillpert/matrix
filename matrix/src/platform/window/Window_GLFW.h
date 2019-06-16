#ifndef Window_GLFW_H
#define Window_GLFW_H

#include "matrix/src/platform/window/Window.h"

#ifdef MX_GLFW_ACTIVE

namespace MX
{
  class Window_GLFW : public Window
  {
  public:    
    MX_API Window_GLFW() = default;
    MX_API ~Window_GLFW() = default;

    MX_API Window_GLFW(const Window_GLFW&) = default;
    MX_API Window_GLFW &operator=(const Window_GLFW&) = default;

    MX_API void update() override;
    MX_API void render() override;
    MX_API bool initialize() override;
    
    MX_API void close() override; 
    MX_API void controllerCallback() const override;

    MX_API void setTitle(const std::string &title) override;
    MX_API void resize(int width, int height) override;        

    MX_API Window_GLFW *getWindow() { return this; }
    
    GLFWwindow* m_Window;
  };
}

#endif

#endif // Window_GLFW_H
