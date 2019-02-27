cmake_minimum_required(VERSION 3.0.0)
set (PROJECT_NAME "Matrix Framework")
project(${PROJECT_NAME} VERSION 0.1.0)

message(${PROJECT_NAME})
message(${CMAKE_SOURCE_DIR})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(external/include)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(application/include)
link_directories(external/libs)

# Macros
IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(MX_DEBUG)
ENDIF ()

IF (MSCV)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
ENDIF ()

IF (WIN32)
    IF (CMAKE_CL_64)
        add_compile_definitions(MX_PLATFORM_WINDOWS_X64)
        add_compile_definitions(MX_BUILD_DLL)
    ENDIF ()
ENDIF ()

# resource directories
add_compile_definitions(MX_TEXTURE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/")
add_compile_definitions(MX_MODEL_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/models/")
add_compile_definitions(MX_SHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/shaders/")

# platform
add_compile_definitions(MX_OPENGL_ACTIVE)
add_compile_definitions(MX_GLFW_ACTIVE)
add_compile_definitions(MX_DEFAULT_CONTROLLER)

# Files for library
file(GLOB FILES_LIB
    "matrix/src/pch/*.cpp"
    "matrix/src/platform/api/*.cpp"
    "matrix/src/platform/window/*.cpp"
    "matrix/src/event/*.cpp"
    "matrix/src/*.cpp"
    "matrix/src/renderer/*.cpp"
)

# Library 
add_library(Matrix SHARED ${FILES_LIB} )

target_link_libraries(Matrix
    ${OPENGL_LIBRARIES}
    glew32s
    glfw3
)

# Files for executable
file(GLOB FILES_EXE
   
)

# Executable
add_executable(Sandbox application/src/EntryPoint.cpp ${FILES_EXE})

target_link_libraries(Sandbox
    Matrix
)

set_target_properties(Matrix Sandbox
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "lib/debug"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "lib/debug"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "bin/debug"

    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "lib/release"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "lib/release"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "bin/release"

    ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "lib/minsizerel"
    LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "lib/minsizerel"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "bin/minsizerel"   
)

set_source_files_properties(framework/pch/stdafx.cpp
    PROPERTIES
    COMPILE_FLAGS "/Ycstdafx.h"
)



