#ifndef WINDOWEVENT_H
#define WINDOWEVENT_H

#include "matrix/src/event/Event.h"

namespace MX
{
  class MX_API WindowEvent : public Event
  {
  public:
    WindowEvent()
    {
      MX_SET_EVENT_TYPE(e_DefaultWindow);
    }
    ~WindowEvent() {}

    void handle() override {}
  };

  class MX_API WindowClosed : public WindowEvent
  {
  public:
    WindowClosed()
    {
      MX_SET_EVENT_TYPE(e_WindowClosed);
    }
    ~WindowClosed() {}

    void handle() override;
  };

  class MX_API WindowResized : public WindowEvent
  {
  public:
    WindowResized(int width, int height)
    {
      setSize(width, height);
      MX_SET_EVENT_TYPE(e_WindowResized);
    }
    ~WindowResized() {}

    void handle() override;
  };
}

#endif // WINDOWEVENT_H