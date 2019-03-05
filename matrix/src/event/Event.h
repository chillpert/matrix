#ifndef EVENT_H
#define EVENT_H

#include "matrix/src/pch/stdafx.h"

#ifdef MX_DEBUG
    #define MX_SET_EVENT_TYPE(x) setEventType(x);
#else
    #define MX_SET_EVENT_TYPE(x)
#endif

enum EventType {
    e_Default = 1, e_DefaultKeyboard = 2, e_DefaultMouse = 3,
    e_KeyboardButtonPressed = 4, e_KeyboardButtonReleased = 5,
    e_MouseButtonPressed = 6, e_MouseButtonReleased = 7,
    e_MouseMoved = 8,
    e_MouseScrolled = 9,
    e_DefaultWindow = 10, e_WindowClosed = 11, e_WindowResized = 12
};

namespace MX {

    class MX_API Event {
    public:
        Event() {
            m_Event = e_Default;
        }
        ~Event() {}

        virtual void handle();
        virtual void printEventType() const;

        int getKeyCode() { return m_KeyCode; }
        EventType getEventType() { return m_Event; }

        void setCoordinates(int xPos, int yPos);
        void setAxis(int xAxis, int yAxis);
        void setKeyCode(int aKeyCode);
        void setEventType(EventType event);
        void setSize(int width, int height);
    protected:
        EventType m_Event;
        int m_X, m_Y;
        int m_KeyCode;
        int m_Xaxis, m_Yaxis;
        int m_Width, m_Height;
    };
}

#endif // EVENT_H