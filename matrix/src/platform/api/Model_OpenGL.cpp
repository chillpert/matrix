#include "matrix/src/platform/api/Model_OpenGL.h"
#include "matrix/src/platform/api/Parser_Wavefront.h"

namespace MX {

    Model_OpenGL::Model_OpenGL(const std::string &name) {
        m_Name = name;
        m_Path = MX_MODEL_PATH + name;
    }

    void Model_OpenGL::setName(const std::string &name) {
        m_Name = name;
        m_Path = MX_MODEL_PATH + name;
    }

    void Model_OpenGL::parse() {
        if (m_Name.find(".obj")) {
            Wavefront_Parser parser(*this);
            parser.start();
        } else {
            MX_FATAL("MX: Model: File format not supported");
        }
    }
}