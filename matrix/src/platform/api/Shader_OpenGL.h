#ifndef SHADER_OPENGL_H
#define SHADER_OPENGL_H

#include "matrix/src/platform/api/Shader.h"

namespace MX {

    class Shader_OpenGL : public Shader {
    public:
        MX_API Shader_OpenGL() {}
        MX_API Shader_OpenGL(const std::string &name);
        MX_API ~Shader_OpenGL() {}
        
        MX_API void create();
        MX_API void use() const;

        MX_API inline unsigned int &getID() { return m_ID; }
    private:
        unsigned int m_ID;
    };

    MX_API void use(Shader_OpenGL &shader);
    MX_API unsigned int compile(unsigned int type, const std::string& source);

    // prints and logs error message if available
    MX_API void errorCheck(const unsigned int &ID, int type);
}

#endif // SHADER_OPENGL_H