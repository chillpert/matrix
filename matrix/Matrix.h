#ifndef MATRIX_H
#define MATRIX_H

// application
#include "matrix/src/Application.h"

// world and levels
#include "matrix/src/layers/World.h"
#include "matrix/src/layers/Node.h"
#include "matrix/src/layers/Level.h"

// debugging
#ifdef MX_DEBUG
  #include "matrix/src/Logger.h"
#endif

#include "matrix/src/Camera.h"

// model
#include "matrix/src/platform/api/Model.h"
#ifdef MX_OPENGL_ACTIVE
  #include "matrix/src/platform/api/Model_OpenGL.h"
#elif MX_DIRECTX_ACTIVE
  #include "matrix/src/platform/api/Model_DirectX.h"
#endif
  #include "matrix/src/platform/api/Parser_Wavefront.h"

// layers
#include "matrix/src/layers/Layer.h"
#include "matrix/src/layers/LayerStack.h"

// controller
#include "matrix/src/controller/Controller.h"

// event

// platform
  // api
  #include "matrix/src/platform/api/Shader.h"
  #ifdef MX_OPENGL_ACTIVE
    #include "matrix/src/platform/api/Shader_OpenGL.h"
  #elif MX_DIRECTX_ACTIVE
    #include "matrix/src/platform/api/Shader_DirectX.h"
  #endif

  // gui

  // window
  #include "matrix/src/platform/window/Window.h"

  #ifdef MX_SDL2_ACTIVE
    #include "SDL2/SDL.h"
  #elif MX_GLFW_ACTIVE
    #include <GLFW/glfw3.h>
  #endif

#endif // MATRIX_H