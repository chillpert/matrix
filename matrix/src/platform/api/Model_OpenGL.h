#ifndef MODEL_OPENGL_H
#define MODEL_OPENGL_H

#include "matrix/src/platform/api/Model.h"

namespace MX {

    class Model_OpenGL : public Model {
    public:    
        MX_API Model_OpenGL() {}
        MX_API Model_OpenGL(const std::string &name);
        MX_API ~Model_OpenGL() {}

        MX_API void parse() override;

        MX_API void setName(const std::string &name);
    };
}

#endif // MODEL_OPENGL_H