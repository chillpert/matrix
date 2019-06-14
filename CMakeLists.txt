cmake_minimum_required(VERSION 3.14.4)
set (PROJECT_NAME "Matrix Framework")
project(${PROJECT_NAME} VERSION 0.2.1)

cmake_policy(SET CMP0072 OLD)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
      "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

message(${PROJECT_NAME})

########### CHANGE THIS #############
# needs clean reconfigure
option(USE_GLFW "use GLFW" OFF)
option(USE_SDL2 "use SDL2" ON)

option(USE_OPENGL "use OpenGL" ON)
option(USE_DIRECTX "use DirectX" OFF)

option(USE_IMGUI "use ImGui" ON)
option(LOG_WINDOW_EVENTS "log window events" OFF)
#####################################

# config for Matrix Framework
include(${PROJECT_SOURCE_DIR}/matrix/CMakeLists.txt)

# config for your application
include(${PROJECT_SOURCE_DIR}/application/CMakeLists.txt)