cmake_minimum_required(VERSION 3.0.0)
set (PROJECT_NAME "Matrix Framework")
project(${PROJECT_NAME} VERSION 0.1.0)

cmake_policy(SET CMP0072 OLD)

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
include(${CMAKE_CURRENT_SOURCE_DIR}/matrix/CMakeLists.txt)

# config for your application
include(${CMAKE_CURRENT_SOURCE_DIR}/application/CMakeLists.txt)