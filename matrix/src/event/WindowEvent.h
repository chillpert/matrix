#ifndef WINDOWEVENT_H
#define WINDOWEVENT_H

#include "Event.h"

namespace MX
{
  class MX_API WindowResized : public Event
  {
  public:
    WindowResized(unsigned int width, unsigned int height);

    EVENT_CLASS_TYPE(WindowResized)
    EVENT_CLASS_CATEGORY(Application)

    unsigned int getWidth() const { return m_width; }
    unsigned int getHeight() const { return m_height; }

    void handle() override;
    std::string toString() const;

  private:
    unsigned int m_width;
    unsigned int m_height;
  };

  class MX_API WindowClosed : public Event
  {
  public:
    EVENT_CLASS_TYPE(WindowClosed)
    EVENT_CLASS_CATEGORY(Application)

    std::string toString() const;
    void handle() override;
  };
}

#endif // WINDOWEVENT_H