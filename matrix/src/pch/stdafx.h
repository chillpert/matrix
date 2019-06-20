#ifndef STDAFX_H
#define STDAFX_H

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
  #undef main

  // maths
  #define GLM_ENABLE_EXPERIMENTAL 
  #include <glm/gtx/string_cast.hpp>
  #include <glm/glm.hpp>
  #include <glm/gtc/matrix_transform.hpp>
  #include <glm/gtc/type_ptr.hpp>

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

// project files
#include <Utils.h>
#include <Logger.h>
#include <API_ErrorHandling.h>
#include <MatrixExceptions.h>

#endif // STDAFX_H