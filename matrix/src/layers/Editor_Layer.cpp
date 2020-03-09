#include "Editor_Layer.h"
#include "Application.h"

namespace MX
{
  #define ERROR_CHECK MX_ASSERT(MX_GUI != nullptr, "MX: Layer: Editor: Is nullptr")

  Editor_Layer::Editor_Layer(const std::string& name)
    : Layer(name)
  {
    MX_GUI = std::make_unique<GUI_Editor>();
  }

  void Editor_Layer::onAttach()
  {
    ERROR_CHECK;
    MX_GUI->initialize();
  }

  void Editor_Layer::onDetach()
  {
    ERROR_CHECK;
    MX_GUI->clean();
  }

  void Editor_Layer::onUpdate()
  {
    ERROR_CHECK;
    MX_GUI->update();
  }

  void Editor_Layer::onRender()
  {
    ERROR_CHECK;
    MX_GUI->render();
  }

  void Editor_Layer::onEvent(Event& event)
  {
    ERROR_CHECK;
  }
}