cmake_minimum_required(VERSION 3.0.0)
set (PROJECT_NAME "Matrix Framework")
project(${PROJECT_NAME} VERSION 0.1.0)

message(${PROJECT_NAME})

########### CHANGE THIS #############
# needs clean reconfigure
option(USE_GLFW "use GLFW" ON)      
option(USE_SDL2 "use SDL2" OFF)        
                                     
option(USE_OPENGL "use OpenGL" ON)   
option(USE_DIRECTX "use DirectX" OFF)

option(USE_IMGUI "use ImGui" ON)
#####################################

# config for Matrix Framework
include(${CMAKE_CURRENT_SOURCE_DIR}/matrix/CMakeLists.txt)
# config for your application
include(${CMAKE_CURRENT_SOURCE_DIR}/application/CMakeLists.txt)