#ifndef EVENT_H
#define EVENT_H

#include "stdafx.h"

#ifdef MX_DEBUG
  #define MX_SET_EVENT_TYPE(x) setEventType(x);
#else
  #define MX_SET_EVENT_TYPE(x)
#endif

enum class EventType
{
  None = 0,

  KeyboardButtonPressed, KeyboardButtonReleased,

  MouseButtonPressed, MouseButtonReleased,
  MouseMoved,
  MouseScrolled,
  
  WindowClosed, WindowResized
};

// uses bit field
enum EventCategory
{
  None = 0,
  Application = (1 << 0),
  Input = (1 << 1),
  Keyboard = (1 << 2),
  Mouse = (1 << 3),
  MouseButton = (1 << 4)
};

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::##type; }\
	virtual EventType getEventType() const override { return getStaticType(); }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

namespace MX 
{
  class MX_API Event 
  {
    friend class EventDispatcher;
  public:
    virtual EventType getEventType() const = 0;
    virtual int getCategoryFlags() const = 0;

    virtual void handle() = 0;
    virtual std::string toString() const = 0;

    inline bool isInCategory(EventCategory category) { return getCategoryFlags() & category; }

  protected:
    bool m_handled = false;
  };

  
  class EventDispatcher
  {
    template<typename T>
    using EventFn = std::function<bool(T&)>;
  
  public:
    EventDispatcher(Event& event)
      : m_event(event) { }

    template<typename T>
    bool dispatch(EventFn<T> func)
    {
      if (m_event.getEventType() == T::getStaticType())
      {
        m_event.m_handled = func(*(T*)&m_event);
        return true;
      }
      return false;
    }

  private:
    Event& m_event;
  };

  inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.toString(); }
}

#endif // EVENT_H