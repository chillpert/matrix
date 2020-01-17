#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H

#include "Event.h"

namespace MX 
{

  class MX_API KeyboardButtonEvent : public Event
  {
  public:
    inline int getKeyCode() const { return m_keycode; }

    EVENT_CLASS_CATEGORY(Keyboard | Input)

    void handle() override {}
    virtual std::string toString() const = 0;

  protected:
    KeyboardButtonEvent(int keycode);

    int m_keycode;
  };

  class MX_API KeyboardButtonPressed : public KeyboardButtonEvent
  {
  public:
    KeyboardButtonPressed(int keycode, int repeat_count = 0);

    EVENT_CLASS_TYPE(KeyboardButtonPressed)

    int getRepeatCount() const { return m_repeat_count; }

    void handle() override;
    std::string toString() const;
  
  private:
    int m_repeat_count;
  };

  class MX_API KeyboardButtonReleased : public KeyboardButtonEvent
  {
  public:
    KeyboardButtonReleased(int keycode);

    EVENT_CLASS_TYPE(KeyboardButtonReleased);

    void handle() override;
    std::string toString() const;
  };
}

#endif // KEYBOARDEVENT_H