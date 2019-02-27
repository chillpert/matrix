#include "matrix/src/platform/api/API_OpenGL.h"

namespace Matrix {

    bool API_OpenGL::createContext() const {
        glewExperimental = GL_TRUE; 
        GLenum glewError = glewInit();
        if (glewError != GLEW_OK) {
            MX_FATAL("GLEW initialisation");
            return false;
        } else {
            MX_SUCCESS("OpenGL context");
            return true;
        }
    }

    void API_OpenGL::render() const {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    }
}
