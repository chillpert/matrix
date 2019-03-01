#ifndef API_OPENGL_H
#define API_OPENGL_H

#include "matrix/src/platform/api/API.h"

namespace MX {

    class MX_API API_OpenGL : public API {
    public:
        API_OpenGL() {}
        ~API_OpenGL() {}

        bool createContext() const override;
        void render() const override; 
    private:
    
    };
}

#endif // API_OPENGL_H