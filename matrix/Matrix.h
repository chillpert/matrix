#ifndef MATRIX_H
#define MATRIX_H

// application
#include "matrix/src/Application.h"
#include "matrix/src/Logger.h"
#include "matrix/src/Camera.h"
#include "matrix/src/platform/api/Model.h"
#include "matrix/src/platform/api/Model_OpenGL.h"
#include "matrix/src/platform/api/Parser_Wavefront.h"
// testing classes
#include "matrix/src/Model_Test.h"
#include "matrix/src/Shader_Test.h"
#include "matrix/src/Camera_Test.h"
// layers
#include "matrix/src/layers/Layer.h"
#include "matrix/src/layers/LayerStack.h"
// controller
#include "matrix/src/controller/Controller.h"
// event

// platform
  // api
  #include "matrix/src/platform/api/Shader.h"
  #include "matrix/src/platform/api/Shader_OpenGL.h"
  #include "matrix/src/platform/api/Shader_DirectX.h"
  // gui

  // window
  #include "matrix/src/platform/window/Window.h"

#endif // MATRIX_H