#include "MousePicker.h"
#include "Ray.h"
#include "Application.h"
#include "Controller.h"

namespace MX
{
  bool MousePicker::initialize()
  {
    return true;
  }

  void MousePicker::update()
  {
    auto mouse = ImGui::GetMousePos();
    
    float x = (2.0f * mouse.x) / 1400.0f - 1.0f;
    float y = 1.0f - (2.0f * mouse.y) / 800.0f;
    float z = 1.0f;
    glm::vec3 ray_nds = glm::vec3(x, y, z);
    glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0f, 1.0f);

    if (MX_SCENE != nullptr)
    {
      glm::mat4 projection_matrix = MX_CAMERA.getProjectionMatrix();
      glm::vec4 ray_eye = glm::inverse(projection_matrix) * ray_clip;
      ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);

      glm::mat4 view_matrix = MX_CAMERA.getViewMatrix();
      glm::vec4 temp = glm::inverse(view_matrix) * ray_eye;
      ray_wor = glm::vec3(temp.x, temp.y, temp.z);
      ray_wor = glm::normalize(ray_wor);
    }
  }
}