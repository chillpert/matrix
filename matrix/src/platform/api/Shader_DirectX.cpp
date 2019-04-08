#include "matrix/src/platform/api/Shader_DirectX.h"

namespace MX {

    Shader_DirectX::Shader_DirectX(const std::string &name) {
        m_Name = name;
        m_VsPath.append(name + ".vert");
        m_FsPath.append(name + ".frag");
    }
}