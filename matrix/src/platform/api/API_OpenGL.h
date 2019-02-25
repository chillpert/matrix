#ifndef API_OPENGL_H
#define API_OPENGL_H

#define GLEW_STATIC
#include <GL/glew.h>

#include "matrix/src/platform/api/API.h"
#include "matrix/src/Core.h"

namespace Matrix {

    class MATRIX_API API_OpenGL : public API {
    public:
        API_OpenGL() {}
        ~API_OpenGL() {}

        bool createContext() const override;
        void render() const override; 
    private:
    
    };
}

#endif // API_OPENGL_H