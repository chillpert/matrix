#ifndef GUI_H
#define GUI_H

#ifdef MX_IMGUI_ACTIVE
    #define MX_GUI_TYPE new MX::GUI_ImGui();
#else
    #define MX_GUI_TYPE nullptr;
#endif

#include "matrix/src/pch/stdafx.h"

namespace MX {

    class GUI {
    public:
        MX_API GUI() {}
        MX_API virtual ~GUI() {}

        MX_API virtual void initialize() {} 
        MX_API virtual void render() {}
        MX_API virtual void clean() {}
    };
}

#endif // GUI_H