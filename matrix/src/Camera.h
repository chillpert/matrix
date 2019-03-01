#ifndef CAMERA_H
#define CAMERA_H

#include "matrix/src/pch/stdafx.h"

namespace MX {

    // move camera
    enum m_Camera {
        FORWARDS, BACKWARDS, LEFT, RIGHT, UP, DOWN
    };

    class Camera {
    public:
        ~Camera() {}
    
        MX_API static Camera& get() {
            static Camera instance;
            return instance;
        }

        MX_API void processKeyboard(m_Camera direction, float speed); 
        MX_API void processMouse(float xoffset, float yoffset);

        glm::fmat4& getViewMatrix() { return glm::lookAt(m_Position, m_Position + m_Front, m_WorldUp); }
    private:
        glm::fvec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f); 
        glm::fvec3 m_Front = glm::vec3(-1.0f, 0.0f, 0.0f);
        glm::fvec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::fvec3 m_WorldUp;
        glm::fvec3 m_Right;
    
        Camera();

        void update();
    };
}

#endif // CAMERA_H