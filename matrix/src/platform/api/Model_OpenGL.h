#ifndef MODEL_OPENGL_H
#define MODEL_OPENGL_H

#include "matrix/src/platform/api/Model.h"

namespace MX {

    struct MX_API RGB {
        float r;
        float g;
        float b;
    };

    struct MX_API Material {
        RGB m_Ambient;
        RGB m_Diffuse;
        RGB m_Specular;
        float m_Alpha;
        float m_Shininess;
        std::string m_TexturePath;
    };

    class Model_OpenGL : public Model {
    public:    
        MX_API Model_OpenGL() {}
        MX_API Model_OpenGL(const std::string &name);
        MX_API ~Model_OpenGL() {}

        MX_API void parse();
        MX_API void parse_wavefront();

        MX_API std::string getName() { return m_Name; }
        MX_API std::string getPath() { return m_Path; }
        MX_API const Material &getMaterial() { return material; }
    private:
        std::string m_Name;
        std::string m_Path;

        Material material;
    };

    
}

#endif // MODEL_OPENGL_H