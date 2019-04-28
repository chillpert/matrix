#ifndef STDAFX_H
#define STDAFX_H

// external

  // API
  #ifdef MX_OPENGL_ACTIVE
    #define GLEW_STATIC
    #include <GL/glew.h>
  #elif MX_DIRECTX_ACTIVE

  #else 
    #error "Matrix only supports OpenGL and DirectX"
  #endif

  // window
  #ifdef MX_GLFW_ACTIVE
    #include <GLFW/glfw3.h>
  #elif MX_SDL2_ACTIVE
    #include <SDL2/SDL.h>
    #undef main
  #endif

  // maths
  #include <glm/glm.hpp>
  #include <glm/gtc/matrix_transform.hpp>
  #include <glm/gtc/type_ptr.hpp>

// libraries
#ifdef MX_PLATFORM_WINDOWS_X64
  #include <windows.h> 
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <iterator>
#include <regex>

// project files
#include "matrix/src/Utils.h"
#include "matrix/src/Logger.h"
#include "matrix/src/platform/api/API_ErrorHandling.h"
#include "matrix/src/Core.h"

#endif // STDAFX_H