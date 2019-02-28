cmake_minimum_required(VERSION 3.0.0)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(external/include)
link_directories(external/libs)

# Macros
    # platform
        # api
            IF (USE_OPENGL AND USE_DIRECTX)
                message(FATAL_ERROR "You can not use OpenGL and DirectX simultaneously")
            ELSEIF (NOT USE_OPENGL AND NOT USE_DIRECTX)
                message(FATAL_ERROR "You have to use either OpenGL or DirectX")
            ELSEIF (USE_DIRECTX)
                message("Using DirectX")
                add_compile_definitions(MX_DIRECTX_ACTIVE)
            ELSEIF (USE_OPENGL)
                message("Using OpenGL")
                add_compile_definitions(MX_OPENGL_ACTIVE)
            ENDIF ()
        # window
            IF (USE_GLFW AND USE_SDL2)
                message(FATAL_ERROR "You can not use GLFW and SDL2 simultaneously")
            ELSEIF (NOT USE_GLFW AND NOT USE_SDL2)
                message(FATAL_ERROR "You have to use either SDL2 or GLFW")
            ELSEIF (USE_SDL2)
                add_compile_definitions(MX_SDL2_ACTIVE)
                message("Using SDL2")
            ELSEIF (USE_GLFW)
                message("Using GLFW")
                add_compile_definitions(MX_GLFW_ACTIVE)
            ENDIF ()
        # controller
            add_compile_definitions(MX_DEFAULT_CONTROLLER)

    # compilation
        IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
            add_compile_definitions(MX_DEBUG)
        ENDIF ()

    # precompiled header
        IF (MSCV)
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
        ENDIF ()

    # operating system
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

# files for library
file(GLOB FILES_LIB
    "matrix/src/pch/*.cpp"
    "matrix/src/platform/api/*.cpp"
    "matrix/src/platform/window/*.cpp"
    "matrix/src/event/*.cpp"
    "matrix/src/*.cpp"
    "matrix/src/renderer/*.cpp"
    "matrix/src/controller/*.cpp"
)

# library 
add_library(Matrix SHARED ${FILES_LIB} )

# set window 
IF (USE_GLFW)
    set(WINDOW_LIB ${WINDOW_LIB}
        glfw3
    )
ELSEIF (USE_SDL2)
    set(WINDOW_LIB ${WINDOW_LIB}   
        SDL2
    )
ENDIF ()

# set api 
IF (USE_OPENGL)
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIRS})
    set(API_LIB ${API_LIB}
        ${OPENGL_LIBRARIES}
        glew32s
    )
ELSEIF (USE_DIRECTX)
    set(API_LIB ${API_LIB}
            
    )
ENDIF ()

target_link_libraries(Matrix
    ${API_LIB}
    ${WINDOW_LIB}
)

set_source_files_properties(matrix/pch/stdafx.cpp
    PROPERTIES
    COMPILE_FLAGS "/Ycstdafx.h"
)