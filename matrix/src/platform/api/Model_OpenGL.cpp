#include "matrix/src/platform/api/Model_OpenGL.h"

namespace MX {

    Model_OpenGL::Model_OpenGL(const std::string &name) {
        m_Name = name;
        m_Path = MX_MODEL_PATH + name;
    }

    void Model_OpenGL::parse() {
        if (m_Name.find(".obj")) {
            parse_wavefront();
        } else {
            MX_FATAL("MX: Model: File format");
        }
    }

    void Model_OpenGL::parse_wavefront() {
        std::ifstream stream(m_Path);

        
    }
}