#include "matrix/src/renderer/Shader.h"

#ifndef M_RESOURCE_PATH 
    #error Resource path is not defined
#else
    #define M_TEXTURE_PATH M_RESOURCE_PATH "textures/"
    #define M_SHADER_PATH  M_RESOURCE_PATH "shaders/"
    #define M_MODEL_PATH   M_RESOURCE_PATH "models/"
    #pragma message ("TEXTURES LOCATED AT: " M_TEXTURE_PATH)
    #pragma message (" SHADERS LOCATED AT: " M_SHADER_PATH)
    #pragma message ("  MODELS LOCATED AT: " M_MODEL_PATH)

    namespace Matrix {

        Shader::Shader() {}

        Shader::Shader(std::string str) {
            m_VertexSource = str;
            m_FragmentSource = str;
        }

        void Shader::setFile(std::string str) {
            m_VertexSource = str;
            m_FragmentSource = str;
        }

        std::string parse(const std::string& filepath) {
        	std::ifstream stream(std::string(M_RESOURCE_PATH) + "shaders/" + filepath);
        	std::string line;
        	std::stringstream ss[1];

        	while (getline(stream, line)) {
        		ss[0] << line << '\n';
        	}
        	return ss[0].str();
        }

        unsigned int Shader::compile(unsigned int type, const std::string& source) {
        	unsigned int id = glCreateShader(type);
        	const char* src = source.c_str();
        	glShaderSource(id, 1, &src, nullptr);
        	glCompileShader(id);

        	GLint success;
            char infoLog[512];
            glGetShaderiv(id, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(id, 512, NULL, infoLog);
                WARN("Failed to comile shader " + std::string(infoLog));
            }
        	return id;
        }


        void Shader::create() {
            m_ID = glCreateProgram();
        	unsigned int vs = compile(GL_VERTEX_SHADER, parse(m_VertexSource + ".vert"));
        	unsigned int fs = compile(GL_FRAGMENT_SHADER, parse(m_FragmentSource + ".frag"));

        	glAttachShader(m_ID, vs);
        	glAttachShader(m_ID, fs);
        	glLinkProgram(m_ID);
        	glValidateProgram(m_ID);

        	int success;
            char infoLog[512];
        	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
                WARN("Failed to link shader program: " + m_VertexSource);
            }
        	glDeleteShader(vs);
        	glDeleteShader(fs);
        }

        unsigned int &Shader::getID() {
            return m_ID;
        }

        void Shader::use() { 
            glUseProgram(m_ID); 
        }

        void Shader::setBool(const std::string &name, bool value) const {         
            glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value); 
        }

        void Shader::setInt(const std::string &name, int value) const { 
            glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value); 
        }

        void Shader::setFloat(const std::string &name, float value) const { 
            glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value); 
        }

        void Shader::setfVec2(const std::string &name, const glm::fvec2 &value) const { 
            glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]); 
        }
        void Shader::setfVec2(const std::string &name, float x, float y) const { 
            glUniform2f(glGetUniformLocation(m_ID, name.c_str()), x, y); 
        }

        void Shader::setfVec3(const std::string &name, const glm::fvec3 &value) const { 
            glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]); 
        }
        void Shader::setfVec3(const std::string &name, float x, float y, float z) const { 
            glUniform3f(glGetUniformLocation(m_ID, name.c_str()), x, y, z); 
        }

        void Shader::setfVec4(const std::string &name, const glm::fvec4 &value) const { 
            glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]); 
        }
        void Shader::setfVec4(const std::string &name, float x, float y, float z, float w) { 
            glUniform4f(glGetUniformLocation(m_ID, name.c_str()), x, y, z, w); 
        }

        void Shader::setfMat2(const std::string &name, const glm::fmat2 &mat) const {
            glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        void Shader::setfMat3(const std::string &name, const glm::fmat3 &mat) const {
            glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        void Shader::setfMat4(const std::string &name, const glm::fmat4 &mat) const {
            glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        void Shader::setView(const glm::fmat4 &mat) const {
            glUseProgram(m_ID);
            glUniformMatrix4fv(glGetUniformLocation(m_ID, "view"), 1, GL_FALSE, &mat[0][0]);
        }

        void Shader::setProjection(const glm::fmat4 &mat) const {
            glUseProgram(m_ID);
            glUniformMatrix4fv(glGetUniformLocation(m_ID, "projection"), 1, GL_FALSE, &mat[0][0]);
        }

        void Shader::setModel(const glm::fmat4 &mat) const {
            glUseProgram(m_ID);
            glUniformMatrix4fv(glGetUniformLocation(m_ID, "model"), 1, GL_FALSE, &mat[0][0]);
        }

    }

#endif