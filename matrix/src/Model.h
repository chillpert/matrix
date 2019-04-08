#ifndef MODEL_H
#define MODEL_H

#include "matrix/src/pch/stdafx.h"

namespace MX {

    struct MX_API vertexInfo {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    };

    struct MX_API modelObject {
        unsigned int VAO = 0;
        unsigned int VBO = 0;
        unsigned int NBO = 0;
        unsigned int TBO = 0;
        unsigned int EBO = 0;
        unsigned int draw_mode = 0;
        unsigned int num_elements = 0;
    };

    class Model {
    public:
        MX_API Model() {};
        MX_API Model(unsigned short amount);
        MX_API Model(const std::string &path);

        MX_API void toString();
        MX_API modelObject &getModelObject();
        MX_API void parseObj(const std::string path);
        MX_API void splitF(const std::string& str);
        MX_API void sort();
        MX_API void setGeometry(unsigned int draw_mode);
        MX_API void setVertexAttributes();
        MX_API void draw();
        MX_API void instanceDraw(int amount);

        MX_API std::vector<glm::vec3> getVertices() { return out_vertices; }

    private:
        std::vector<glm::vec3> out_vertices;
        std::vector<glm::vec2> out_textures;
        std::vector<glm::vec3> out_normals;
        std::vector<glm::vec3> vertexPos;
        std::vector<glm::vec3> normalPos;
        std::vector<glm::vec2> texturePos;
        std::vector<int> vertexIndex;
        std::vector<int> textureIndex;
        std::vector<int> normalIndex;

        std::string file_path;

        bool gotPosition = false;
        bool gotNormal = false;
        bool gotTexture = false;
        bool gotIndex = false;

        unsigned short vertexAttribs;

        modelObject model_object;
    };
}

#endif // MODEL_H