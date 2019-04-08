#include "matrix/src/platform/api/API_OpenGL.h"

namespace MX {

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
        MX_API_ERROR;
    }

    void API_OpenGL::update() const {
        glEnable(GL_DEPTH_TEST);
    }

    void API_OpenGL::render() const {
        
    }

    void API_OpenGL::clear() const {
        glViewport(0, 0, 1200, 600);
        glClearColor(0.0f, 0.0f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}
