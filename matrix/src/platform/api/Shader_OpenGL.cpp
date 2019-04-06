#include "matrix/src/platform/api/Shader_OpenGL.h"

namespace MX {

    Shader_OpenGL::Shader_OpenGL(const std::string &name) {
        m_VsPath.append(name + ".vert");
        m_FsPath.append(name + ".frag");
    }

    void Shader_OpenGL::use() const {
        glUseProgram(m_ID); 
    }

    void Shader_OpenGL::create() {
        m_ID = glCreateProgram();
        
	    unsigned int vs = compile(GL_VERTEX_SHADER, parseFile(m_VsPath));
	    unsigned int fs = compile(GL_FRAGMENT_SHADER, parseFile(m_FsPath));

	    glAttachShader(m_ID, vs);
	    glAttachShader(m_ID, fs);
	    glLinkProgram(m_ID);
	    glValidateProgram(m_ID);

        errorCheck(m_ID, GL_LINK_STATUS);
        
	    glDeleteShader(vs);
	    glDeleteShader(fs);

        MX_SUCCESS("MX: OpenGL: Shader at\n" + m_VsPath + "\n" + m_FsPath);
    }

    void use(Shader_OpenGL &shader) {
        glUseProgram(shader.getID());
    }

    unsigned int compile(unsigned int type, const std::string& source) {
        unsigned int ID = glCreateShader(type);
	    const char* src = source.c_str();
	    glShaderSource(ID, 1, &src, nullptr);
	    glCompileShader(ID);

        errorCheck(ID, GL_COMPILE_STATUS);

	    return ID;
    }

    void errorCheck(const unsigned int &ID, int type) {
        int success;
        char infoLog[512];
	    glGetProgramiv(ID, type, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            MX_FATAL("MX: Shader: " + std::string(infoLog));
        }
    }
}