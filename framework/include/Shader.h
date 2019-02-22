#ifndef SHADER_H
#define SHADER_H

#include "Core.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

namespace Matrix {

class MATRIX_API Shader {

public:
    Shader();
    Shader(std::string str);
    
    void setFile(std::string str);
    unsigned int compile(unsigned int type, const std::string& source);
    void create();
    unsigned int &getID();

    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setfVec2(const std::string &name, const glm::fvec2 &value) const;
    void setfVec2(const std::string &name, float x, float y) const;
    void setfVec3(const std::string &name, const glm::fvec3 &value) const;
    void setfVec3(const std::string &name, float x, float y, float z) const;
    void setfVec4(const std::string &name, const glm::fvec4 &value) const;
    void setfVec4(const std::string &name, float x, float y, float z, float w);
    void setfMat2(const std::string &name, const glm::fmat2 &mat) const;
    void setfMat3(const std::string &name, const glm::fmat3 &mat) const;
    void setfMat4(const std::string &name, const glm::fmat4 &mat) const;
    void setView(const glm::fmat4 &mat) const;
    void setProjection(const glm::fmat4 &mat) const;
    void setModel(const glm::fmat4 &mat = glm::fmat4(1.0f)) const;

private:
    unsigned int m_ID;
    std::string m_VertexSource;
	std::string m_FragmentSource;
};

MATRIX_API std::string parse(const std::string& filepath);

}

#endif // SHADER_H