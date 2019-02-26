#include "matrix/src/event/Event.h"

namespace Matrix {

    void Event::printEventType() const {
        if (event == 0) 
            INFO("Event: Default");
    }

    void Event::handle() {
        
    }
}