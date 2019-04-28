#ifndef CAMERA_TEST_H
#define CAMERA_TEST_H

#include "matrix/src/pch/stdafx.h"

namespace MX {

    // move camera
    enum m_Camera_Test {
        m_forwards, m_backwards, m_down, m_up, m_left, m_right
    };

    // follow camera
    enum f_Camera_Test {
        f_behind, f_front, f_left, f_right, f_top, f_bottom
    };

    class Camera_Test {

    public:
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 up;
        glm::vec3 right;
        float yaw = -90.0f;
        float pitch = 0.0f;
        float sensitivity = 0.06f;
        float fov = 45.0f;

        MX_API static Camera_Test &get() {
            static Camera_Test instance;
            return instance;
        }

        MX_API void proessKeyboard(m_Camera_Test direction, float cameraSpeed);
        MX_API void processMouseMotion(float xoffset, float yoffset);

        MX_API void neutralizeAngles();

        MX_API glm::mat4 getViewMatrix() { return glm::lookAt(position, position + front, up); }
        MX_API glm::mat4 getProjectionMatrix() { return glm::perspective(glm::radians(fov), (float)1200 / (float)600, 0.1f, 100.0f); }

    private:
        MX_API Camera_Test();
        MX_API void updateCameraVectors();
    };
}

#endif // CAMERA_TEST_H