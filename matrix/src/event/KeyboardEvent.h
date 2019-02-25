#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H

#include "matrix/src/event/Event.h"

namespace Matrix {

    class KeyboardEvent : public Event {
    public:
        KeyboardEvent() {}
        ~KeyboardEvent() {}

        void printEventType() const override;
    protected:
        int m_KeyCode;
    private:
        EventType event = e_DefaultKeyboard;
    };

    class KeyboardButtonPressed : public KeyboardEvent {
    public:
        KeyboardButtonPressed(int button)
            : m_KeyCode(button) {}
        ~KeyboardButtonPressed() {}

        void printEventType() const override;
    private:
        EventType event = e_KeyboardButtonPressed;
        int m_KeyCode;
    };

    class KeyboardButtonReleased : public KeyboardEvent {
    public:
        KeyboardButtonReleased(int button) 
            : m_KeyCode(button) {}
        ~KeyboardButtonReleased() {}

        void printEventType() const override;
    private:
        EventType event = e_KeyboardButtonReleased;
        int m_KeyCode;
    };
}

#endif // KEYBOARDEVENT_H