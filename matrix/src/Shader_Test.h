#ifndef SHADER_TEST_H
#define SHADER_TEST_H

#include "matrix/src/pch/stdafx.h"

namespace MX {

    class Shader_Test {

    public:
        MX_API Shader_Test();
        MX_API Shader_Test(std::string str);

        MX_API void setSource(std::string str);
        MX_API unsigned int compileShader(unsigned int type, const std::string& source);
        MX_API void createShader();
        MX_API unsigned int &getID();

        MX_API void use();
        MX_API void setBool(const std::string &name, bool value) const;
        MX_API void setInt(const std::string &name, int value) const;
        MX_API void setFloat(const std::string &name, float value) const;
        MX_API void setfVec2(const std::string &name, const glm::fvec2 &value) const;
        MX_API void setfVec2(const std::string &name, float x, float y) const;
        MX_API void setfVec3(const std::string &name, const glm::fvec3 &value) const;
        MX_API void setfVec3(const std::string &name, float x, float y, float z) const;
        MX_API void setfVec4(const std::string &name, const glm::fvec4 &value) const;
        MX_API void setfVec4(const std::string &name, float x, float y, float z, float w);
        MX_API void setfMat2(const std::string &name, const glm::fmat2 &mat) const;
        MX_API void setfMat3(const std::string &name, const glm::fmat3 &mat) const;
        MX_API void setfMat4(const std::string &name, const glm::fmat4 &mat) const;
        MX_API void setView(const glm::fmat4 &mat) const;
        MX_API void setProjection(const glm::fmat4 &mat) const;
        MX_API void setModel(const glm::fmat4 &mat = glm::fmat4(1.0f)) const;

    private:
        unsigned int ID;
        std::string vertexSource;
    	std::string fragmentSource;
    };

    MX_API std::string ParseShader(const std::string& filepath);
}

#endif // SHADER_TEST_H