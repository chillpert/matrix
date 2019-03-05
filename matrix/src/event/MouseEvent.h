#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include "matrix/src/event/Event.h"

namespace MX {

    class MX_API MouseEvent : public Event {
    public:
        MouseEvent() {
            MX_SET_EVENT_TYPE(e_DefaultMouse);
        }
        ~MouseEvent() {}

        void handle() override {};
    };

    class MX_API MouseButtonPressed : public MouseEvent {
    public:
        MouseButtonPressed(int button) {
            setKeyCode(button);
            MX_SET_EVENT_TYPE(e_MouseButtonPressed);
        }
        ~MouseButtonPressed() {}

        void handle() override;
    };

    class MX_API MouseButtonReleased : public MouseEvent {
    public:
        MouseButtonReleased(int button) {
            setKeyCode(button);
            MX_SET_EVENT_TYPE(e_MouseButtonReleased);
        }
        ~MouseButtonReleased() {}

        void handle() override;
    };

    class MX_API MouseMoved : public MouseEvent {
    public:
        MouseMoved(int x, int y) {
            setCoordinates(x, y);
            MX_SET_EVENT_TYPE(e_MouseMoved);
        }
        ~MouseMoved() {}

        void handle() override;
    };

    class MX_API MouseScrolled : public MouseEvent {
    public:
        MouseScrolled(int xAxis, int yAxis) {
            setAxis(xAxis, yAxis);
            MX_SET_EVENT_TYPE(e_MouseScrolled);
        }
        ~MouseScrolled() {}

        void handle() override;
    };
}

#endif // MOUSEEVENT_H