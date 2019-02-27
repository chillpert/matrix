#ifndef STDAFX_H
#define STDAFX_H

#ifdef MX_PLATFORM_WINDOWS_X64
    #include <windows.h> 
#endif

// external libraries
#include "matrix/src/Utils.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// libraries
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>

// project files
#include "matrix/src/Logger.h"
#include "matrix/src/Core.h"

#endif // STDAFX_H