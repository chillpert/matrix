#include "Editor_Dock.h"

namespace MX
{
  void Editor_Dock::initialize()
  {
  
  }

  void Editor_Dock::render()
  {
    if (ImGui::Begin("TESTING PLAYBACK SOUND"))
    {
      ImGui::Text("Let's jump right into it!");
      ImGui::End();
    }
  }
}
