#ifndef EVENT_H
#define EVENT_H

#include "matrix/src/pch/stdafx.h"

enum EventType {
    e_Default = 1, e_DefaultKeyboard = 2, e_DefaultMouse = 3,
    e_KeyboardButtonPressed = 4, e_KeyboardButtonReleased = 5,
    e_MouseButtonPressed = 6, e_MouseButtonReleased = 7,
    e_MouseMoved = 8
};

namespace Matrix {

    class MATRIX_API Event {
    public:
        Event() {}
        ~Event() {}

        virtual void handle();
        virtual void printEventType() const;
    protected:
        EventType event = e_Default;
        int m_X, m_Y;
        int m_KeyCode;
    };
}

#endif // EVENT_H