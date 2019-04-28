#include "matrix/src/Camera_Test.h"

namespace MX {

    Camera_Test::Camera_Test() {
        updateCameraVectors();
    }

    void Camera_Test::processMouseMotion(float xoffset, float yoffset) {
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if (yaw > 360.0f) {
            yaw = fmod(yaw, 360.0f);
        }
        if (yaw < 0.0f) {
            yaw = 360.0f + fmod(yaw, 360.0f);
        }

        if (pitch > 89.0f) {
            pitch = 89.0f;
        }
        if (pitch < -89.0f) {
            pitch = -89.0f;
        }

        updateCameraVectors();
    }

    void Camera_Test::proessKeyboard(m_Camera_Test direction, float cameraSpeed) {
        switch (direction) {
        case m_forwards:
            position += front * cameraSpeed;
        break;
        case m_backwards:
            position -= front * cameraSpeed;
        break;
        case m_left:
            position -= right * cameraSpeed; 
        break;
        case m_right:
            position += right * cameraSpeed;
        break;
        case m_up:
            position = glm::vec3(position[0], position[1] + cameraSpeed, position[2]);
        break;
        case m_down:
            position = glm::vec3(position[0], position[1] - cameraSpeed, position[2]);
        break;
        }
    }

    void Camera_Test::neutralizeAngles() {
        pitch = 0.0f;
        updateCameraVectors();
    }

    void Camera_Test::updateCameraVectors() {
        glm::vec3 t_front;
        t_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        t_front.y = sin(glm::radians(pitch));
        t_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(t_front); 
        right = glm::normalize(glm::cross(front, worldUp));  
        up    = glm::normalize(glm::cross(right, front));
    }


}