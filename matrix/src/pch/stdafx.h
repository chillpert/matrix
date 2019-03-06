#ifndef STDAFX_H
#define STDAFX_H

#ifdef MX_PLATFORM_WINDOWS_X64
    #include <windows.h> 
#endif

// external libraries
#include "matrix/src/Utils.h"

#ifdef MX_GLFW_ACTIVE
    #include <GLFW/glfw3.h>
#elif MX_SDL2_ACTIVE
    #include <SDL2/SDL.h>
    #undef main
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// libraries
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <algorithm>

// project files
#include "matrix/src/Logger.h"
#include "matrix/src/Core.h"

#endif // STDAFX_H