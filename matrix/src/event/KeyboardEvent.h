#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H

#include "matrix/src/event/Event.h"

namespace MX {

    class MX_API KeyboardEvent : public Event {
    public:
        KeyboardEvent() {}
        ~KeyboardEvent() {}

        void handle() override;
        void printEventType() const override;
    protected:
        int m_KeyCode;
    private:
        EventType event = e_DefaultKeyboard;
    };

    class MX_API KeyboardButtonPressed : public KeyboardEvent {
    public:
        KeyboardButtonPressed(int button)
            : m_KeyCode(button) {}
        ~KeyboardButtonPressed() {}

        void handle() override;
        void printEventType() const override;
    private:
        EventType event = e_KeyboardButtonPressed;
        int m_KeyCode;
    };

    class MX_API KeyboardButtonReleased : public KeyboardEvent {
    public:
        KeyboardButtonReleased(int button) 
            : m_KeyCode(button) {}
        ~KeyboardButtonReleased() {}

        void handle() override;
        void printEventType() const override;
    private:
        EventType event = e_KeyboardButtonReleased;
        int m_KeyCode;
    };
}

#endif // KEYBOARDEVENT_H