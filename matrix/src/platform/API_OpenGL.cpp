#include "matrix/src/platform/API_OpenGL.h"
#include "Matrix/src/Logger.h"

#ifdef OPENGL_ACTIVE

namespace Matrix {

    bool API_OpenGL::createContext() const {
        glewExperimental = GL_TRUE; 
        GLenum glewError = glewInit();
        if (glewError != GLEW_OK) {
            FATAL("GLEW initialisation");
            return false;
        } else {
            SUCCESS("OpenGL context created");
            return true;
        }
    }

    void API_OpenGL::render() const {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    }
}

#endif