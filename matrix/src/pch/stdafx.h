#ifndef STDAFX_H
#define STDAFX_H

#ifdef MX_PLATFORM_UNIX_X64
  #pragma GCC diagnostic ignored "-Wformat-security"
#elif MX_PLATFORM_WINDOWS_X64
  #include <stdint.h>
#endif

// external

  // API
  #ifdef MX_OPENGL_ACTIVE
    #include <GL/glew.h>
  #elif MX_DIRECTX_ACTIVE

  #else 
    #error "Matrix only supports OpenGL and DirectX"
  #endif

  // window
  #include <SDL.h>
  #include <SDL_thread.h>
  #include <SDL_image.h>
  #undef main

  // maths
  #define GLM_ENABLE_EXPERIMENTAL 
  //#include <glm/glm.hpp>
  #include <glm/gtx/string_cast.hpp>
  #include <glm/gtx/transform.hpp>
  #include <glm/gtx/matrix_decompose.hpp>
  #include <glm/gtc/matrix_transform.hpp>
  #include <glm/gtx/quaternion.hpp>
  #include <glm/gtc/type_ptr.hpp>
  #include <glm/gtx/euler_angles.hpp>
  #include <glm/gtx/intersect.hpp>

  // texture loading
  #include <stb_image.h>

// libraries
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <list>
#include <iterator>
#include <regex>
#include <utility>
#include <map>
#include <exception>
#include <typeinfo>
#include <initializer_list>
#include <tuple>
#include <functional>

// project files
#include "Utility.h"
#include "Logger.h"
#include "API_ErrorHandling.h"
#include "MatrixExceptions.h"

#endif // STDAFX_H