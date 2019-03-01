#include "matrix/src/event/Event.h"

namespace MX {

    void Event::printEventType() const {
        if (event == 0) 
            MX_INFO("Event: Default");
    }

    void Event::handle() {
        
    }
}