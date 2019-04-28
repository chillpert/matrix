#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H

#include "matrix/src/event/Event.h"

namespace MX 
{

  class MX_API KeyboardEvent : public Event
  {
  public:
    KeyboardEvent() 
    {
      MX_SET_EVENT_TYPE(e_DefaultKeyboard);
    }
    ~KeyboardEvent() {}

    void handle() override {}
  };

  class MX_API KeyboardButtonPressed : public KeyboardEvent
  {
  public:
    KeyboardButtonPressed(int button) 
    {
      setKeyCode(button);
      MX_SET_EVENT_TYPE(e_KeyboardButtonPressed);
    }
    ~KeyboardButtonPressed() {}

    void handle() override;
  };

  class MX_API KeyboardButtonReleased : public KeyboardEvent
  {
  public:
    KeyboardButtonReleased(int button)
    {
      setKeyCode(button);
      MX_SET_EVENT_TYPE(e_KeyboardButtonReleased);
    }
    ~KeyboardButtonReleased() {}

    void handle() override;
  };
}

#endif // KEYBOARDEVENT_H