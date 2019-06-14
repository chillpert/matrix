cmake_minimum_required(VERSION 3.0.0)
set (PROJECT_NAME "Matrix Framework")
project(${PROJECT_NAME} VERSION 0.1.0)

cmake_policy(SET CMP0072 OLD)

IF (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") OR (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel") AND UNIX))
  set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++14 -Wall")
  set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
  set(CMAKE_CXX_FLAGS "-std=c++17 -Wall")
ENDIF ()

#set(CMAKE_CXX_FLAGS "-Wno-dev")
#add_definitions(${CMAKE_CXX_FLAGS})

message(${PROJECT_NAME})

########### CHANGE THIS #############
# needs clean reconfigure
option(USE_GLFW "use GLFW" OFF)
option(USE_SDL2 "use SDL2" ON)

option(USE_OPENGL "use OpenGL" ON)
option(USE_DIRECTX "use DirectX" OFF)

option(USE_IMGUI "use ImGui" ON)
option(LOG_EVENTS "log window related events" OFF)
#####################################

# config for Matrix Framework
include(${PROJECT_SOURCE_DIR}/matrix/CMakeLists.txt)

# config for your application
include(${PROJECT_SOURCE_DIR}/application/CMakeLists.txt)