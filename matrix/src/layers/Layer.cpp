#include "matrix/src/layers/Layer.h"

namespace MX {

    void Layer::handleEvent() {
        m_Event.handle();
    }
}