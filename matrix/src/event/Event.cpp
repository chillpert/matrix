#include "Event.h"

namespace MX 
{

  void Event::setEventType(EventType event) 
  {
      m_Event = event;
  }

  void Event::setKeyCode(int aKeyCode)
  {
    m_KeyCode = aKeyCode;
  } 

  void Event::setCoordinates(int xPos, int yPos)
  {
    m_X = xPos;
    m_Y = yPos;
  }

  void Event::setAxis(int xAxis, int yAxis)
  {
    m_Xaxis = xAxis;
    m_Yaxis = yAxis;
  }

  void Event::setSize(int width, int height)
  {
    m_Width = width;
    m_Height = height;
  }

  void Event::printEventType() const 
  {
  #ifdef MX_LOG_EVENTS
    switch (m_Event) 
    {
      case 1:
        MX_INFO_LOG("MX: Event: Default");
        break;
      case 2:
        MX_INFO_LOG("MX: Event: DefaultKeyboard");
        break;
      case 3:
        MX_INFO_LOG("MX: Event: DefaultMouse");
        break;
      case 4:
        MX_INFO_LOG("MX: Event: KeyboardButtonPressed: " + std::to_string(m_KeyCode));
        break;
      case 5:
        MX_INFO_LOG("MX: Event: KeyboardButtonReleased: " + std::to_string(m_KeyCode));
        break;
      case 6:
        MX_INFO_LOG("MX: Event: MouseButtonPressed: " + std::to_string(m_KeyCode));
        break;
      case 7:
        MX_INFO_LOG("MX: Event: MouseButtonReleased: " + std::to_string(m_KeyCode));
        break;
      case 8:
        MX_INFO_LOG("MX: Event: MouseMoved: " + std::to_string(m_X) + ", " + std::to_string(m_Y));
        break;
      case 9: 
        MX_INFO_LOG("MX: Event: MouseScrolled: " + std::to_string(m_Xaxis) + ", " + std::to_string(m_Yaxis));
        break;
      case 10:
        MX_INFO_LOG("MX: Event: DefaultWindow"); 
        break; 
      case 11: 
        MX_INFO_LOG("MX: Event: WindowClosed");
        break;
      case 12: 
        MX_INFO_LOG("MX: Event: WindowResized: " + std::to_string(m_Width) + ", " + std::to_string(m_Height));
        break;
      default:
        MX_WARN_LOG("MX: Event: Unkown");
        break;
    }
  #endif
  }

  void Event::handle() 
  {
      
  }
}