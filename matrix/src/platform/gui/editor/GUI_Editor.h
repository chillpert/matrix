#ifndef GUI_EDITOR
#define GUI_EDITOR

#include "GUI_ImGui.h"
#include "Editor_Modules.h"

namespace MX
{
  class GUI_Editor : public GUI_ImGui
  {
  public:
    MX_API GUI_Editor();

    MX_API void initialize() override;
    MX_API void update() override;
    MX_API void render() override;
    MX_API void clean() override;
    MX_API void clear() override;
  
    std::vector<std::pair<std::string, bool*>>* m_visibilities;
    std::map<std::string, std::shared_ptr<ImGui_Window>> m_modules;
  private:
  };
}

#endif // GUI_EDITOR