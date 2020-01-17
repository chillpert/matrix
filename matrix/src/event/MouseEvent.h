#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include "Event.h"

namespace MX 
{
  class MX_API MouseMoved : public Event
  {
  public:
    MouseMoved(float x, float y);

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(Mouse | Input)

    float getX() const { return m_mouse_x; }
    float getY() const { return m_mouse_y; }

    void handle() override;
    std::string toString() const;
  
  private:
    float m_mouse_x;
    float m_mouse_y;
  };

  class MX_API MouseScrolled : public Event
  {
  public:
    MouseScrolled(float offset_x, float offset_y);

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(Mouse | Input)

    float getOffsetX() const { return m_offset_x; }
    float getOffsetY() const { return m_offset_y; }

    void handle() override;
    std::string toString() const;

  private:
    float m_offset_x;
    float m_offset_y;
  };

  class MX_API MouseButtonEvent : public Event
  {
  public:
    EVENT_CLASS_CATEGORY(Mouse | Input)

    int getMouseButton() const { return m_button; }
  
  protected:
    MouseButtonEvent(int button);

    int m_button;
  };

  class MX_API MouseButtonPressed : public MouseButtonEvent
  {
  public:
    MouseButtonPressed(int button);

    EVENT_CLASS_TYPE(MouseButtonPressed)

    void handle() override;
    std::string toString() const;
  };

  class MX_API MouseButtonReleased : public MouseButtonEvent
  {
  public:
    MouseButtonReleased(int button);

    EVENT_CLASS_TYPE(MouseButtonReleased)

    void handle() override;
    std::string toString() const;
  };
}

#endif // MOUSEEVENT_H