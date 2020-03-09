#include "Window_Layer.h"
#include "Application.h"

namespace MX
{
  #define ERROR_CHECK MX_ASSERT(MX_WINDOW != nullptr, "MX: Layer: Editor: Is nullptr")

  Window_Layer::Window_Layer(const std::string& name)
    : Layer(name)
  {
    MX_WINDOW = std::make_unique<Window_SDL2>();
  }

  void Window_Layer::onAttach()
  {
    ERROR_CHECK;
    MX_IS_RUNNING(MX_WINDOW->initialize());
  }

  void Window_Layer::onDetach()
  {
    ERROR_CHECK;
    MX_WINDOW->close();
  }

  void Window_Layer::onUpdate()
  {
    ERROR_CHECK;
    MX_WINDOW->update();
  }

  void Window_Layer::onRender()
  {
    ERROR_CHECK;
    MX_WINDOW->render();
  }

  void Window_Layer::onEvent(Event& event)
  {
    ERROR_CHECK;
  }
}