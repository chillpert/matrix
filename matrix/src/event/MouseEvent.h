#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include "matrix/src/event/Event.h"

namespace MX {

    class MX_API MouseEvent : public Event {
    public:
        MouseEvent() {}
        ~MouseEvent() {}

        void handle() override;
        void printEventType() const override;
    protected:
        int m_KeyCode;
        int m_X, m_Y;
    private:
        EventType event = e_DefaultMouse;
    };

    class MX_API MouseButtonPressed : public MouseEvent {
    public:
        MouseButtonPressed(int button)
            : m_KeyCode(button) {}
        ~MouseButtonPressed() {}

        void handle() override;
        void printEventType() const override;
    private:
        EventType event = e_MouseButtonPressed;
        int m_KeyCode;
    };

    class MX_API MouseButtonReleased : public MouseEvent {
    public:
        MouseButtonReleased(int button)
            : m_KeyCode(button) {}
        ~MouseButtonReleased() {}

        void handle() override;
        void printEventType() const override;
    private:
        EventType event = e_MouseButtonReleased;
        int m_KeyCode;
    };

    class MX_API MouseMoved : public MouseEvent {
    public:
        MouseMoved(int x, int y)
            : m_X(x), m_Y(y) {}
        ~MouseMoved() {}

        void handle() override;
        void printEventType() const override;
    private:
        EventType event = e_MouseMoved;
        int m_X;
        int m_Y;
    };

    class MX_API MouseScrolled : public MouseEvent {
    public:
        MouseScrolled(int xAxis, int yAxis)
            : m_Xaxis(xAxis), m_Yaxis(yAxis) {}
        ~MouseScrolled() {}

        void handle() override;
        void printEventType() const override;
    private:
        EventType event = e_MouseScrolled;
        int m_Xaxis;
        int m_Yaxis;
    };
}

#endif // MOUSEEVENT_H