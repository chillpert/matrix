#include "matrix/src/platform/window/Window.h"

namespace MX
{
  void Window::setTitle(std::string title)
  {
    m_Props.m_Title = title;
    setTitle();
  }

  void Window::resize(int width, int height)
  {
    m_Props.m_Width = width;
    m_Props.m_Height = height;
    resize();
  }
}