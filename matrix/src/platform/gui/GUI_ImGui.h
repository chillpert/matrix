#ifndef GUI_IMGUI_H
#define GUI_IMGUI_H

#include "matrix/src/platform/gui/GUI.h"

namespace MX {

    class GUI_ImGui: public GUI {
    public: 
        MX_API GUI_ImGui() {}
        MX_API ~GUI_ImGui() {}

        MX_API void initialize() override;
        MX_API void update() override;
        MX_API void render() override;
        MX_API void clean() override;
    };
}

#endif // GUI_IMGUI_H