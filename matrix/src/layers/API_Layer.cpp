#include "API_Layer.h"
#include "Application.h"

namespace MX
{
  #define ERROR_CHECK MX_ASSERT(MX_GAPI != nullptr, "MX: Layer: Editor: Is nullptr")

  API_Layer::API_Layer(const std::string& name)
    : Layer(name)
  {
    MX_GAPI = std::make_unique<MX_API_TYPE>();
  }

  void API_Layer::onAttach()
  {
    ERROR_CHECK;
    MX_IS_RUNNING(MX_GAPI->initialize());
  }

  void API_Layer::onDetach()
  {
    ERROR_CHECK;
  }

  void API_Layer::onUpdate()
  {
    ERROR_CHECK;
    MX_GAPI->update();
  }

  void API_Layer::onRender()
  {
    ERROR_CHECK;
    MX_GAPI->render();
  }

  void API_Layer::onEvent(Event& event)
  {
    ERROR_CHECK;
  }
}