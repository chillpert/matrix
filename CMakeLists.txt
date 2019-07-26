cmake_minimum_required(VERSION 3.14.0)
set (PROJECT_NAME "Matrix Framework")
project(${PROJECT_NAME} VERSION 0.2.1)

message(${PROJECT_NAME})

cmake_policy(SET CMP0072 OLD)

if(("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") OR (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel") AND UNIX))
  set(CMAKE_CXX_FLAGS "-std=c++17 -Wall")
endif()

if(NOT CMAKE_BUILD_TYPE)
message("MX: Build type not set. Continuing with: ${CMAKE_BUILD_TYPE}")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
      "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

################### CHANGE THIS ######################
# needs clean reconfigure
option(USE_OPENGL "use OpenGL" ON)
option(USE_DIRECTX "use DirectX" OFF)

option(USE_IMGUI "use ImGui" OFF)
option(GUI_LOG_ALL "log all events in gui logger" OFF)
option(LOG_WINDOW_EVENTS "log window events" OFF)
######################################################

# config for Matrix Framework
include(${PROJECT_SOURCE_DIR}/matrix/CMakeLists.txt)

# config for your application
include(${PROJECT_SOURCE_DIR}/application/CMakeLists.txt)