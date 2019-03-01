#include "matrix/src/Camera.h"

namespace MX {

    Camera::Camera() {
        update();
    }

    void Camera::update() {
        m_Right = glm::normalize(glm::cross(m_Up, m_Front));
        m_WorldUp = glm::normalize(glm::cross(m_Right, m_Front));
    }

    void Camera::processKeyboard(m_Camera direction, float speed) {
        switch (direction) {
            case FORWARDS:

                break;
            case BACKWARDS:

                break;
            case LEFT:

                break;
            case RIGHT:
                
                break;
            case UP:

                break;
            case DOWN:

                break;
            default:
                MX_WARN("Camera direction unkown");
                break;
        }
        update();
    }

    void Camera::processMouse(float xoffset, float yoffset) {
        
        update();
    }
}