cmake_minimum_required(VERSION 3.0.0)

# boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

IF (WIN32)
  IF (CMAKE_CL_64)
    set(BOOST_LIB ${Boost_LIBRARIES}
      "libboost_filesystem-vc141-mt-gd-x64-1_70"
    )
  ENDIF ()
ELSEIF (UNIX)
  find_package(Boost REQUIRED COMPONENTS filesystem) 

  IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
  ENDIF ()
ENDIF ()

# include and link directories
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
        IF (UNIX)
          #find_package(SDL2_REQUIRED)
          #include_directories(${SDL2_INCLUDE_DIRS})
        ENDIF ()
      ELSEIF (USE_GLFW)
        message("Using GLFW")
        add_compile_definitions(MX_GLFW_ACTIVE)
      ENDIF ()

    # log events
      IF (LOG_EVENTS)
        message("Logging events enabled")
        add_compile_definitions(MX_LOG_EVENTS)
      ENDIF ()

    # controller
      add_compile_definitions(MX_DEFAULT_CONTROLLER)

    # gui
      IF (USE_IMGUI)
        message("Using ImGui")
        add_compile_definitions(MX_IMGUI_ACTIVE)
      
      ELSE ()
        message("No GUI selected")
      ENDIF ()

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
  ELSEIF (UNIX)
    add_compile_definitions(MX_PLATFORM_UNIX_X64)
    add_compile_definitions(MX_BUILD_DLL)
  ENDIF ()

  # resource directories
  add_compile_definitions(MX_TEXTURE_PATH="${PROJECT_SOURCE_DIR}/resources/textures/")
  add_compile_definitions(MX_MODEL_PATH="${PROJECT_SOURCE_DIR}/resources/models/")
  add_compile_definitions(MX_SHADER_PATH="${PROJECT_SOURCE_DIR}/resources/shaders/")

# external cpp files

  # IMGUI
  IF (USE_OPENGL)
    set(IMGUI_API ${IMGUI_API}
      "external/include/IMGUI/imgui_impl_opengl3.cpp"
    )

  ELSEIF (USE_DIRECTX)
    set(IMGUI_API ${IMGUI_API}
    
    )
  ENDIF() 

  IF (USE_GLFW)
    set(IMGUI_WINDOW ${IMGUI_WINDOW}
      "external/include/IMGUI/imgui_impl_glfw.cpp"
    )

  ELSEIF (USE_SDL2)
    set(IMGUI_WINDOW ${IMGUI_WINDOW}
      "external/include/IMGUI/imgui_impl_sdl.cpp"
    )
  ENDIF()

  set(IMGUI_FILES ${IMGUI_FILES}
    "external/include/IMGUI/imgui.cpp"
    "external/include/IMGUI/imgui_demo.cpp"
    "external/include/IMGUI/imgui_draw.cpp"
    "external/include/IMGUI/imgui_widgets.cpp"
  )

  IF (USE_IMGUI)
    set(GUI_FILES ${GUI_FILES}
      ${IMGUI_FILES}
      ${IMGUI_API}
      ${IMGUI_WINDOW}
    )
  ELSE ()
    set(GUI_FILES ${GUI_FILES})
  ENDIF ()

# files for library
file(GLOB FILES_LIB
  "matrix/src/controller/*.cpp"
  "matrix/src/event/*.cpp"
  "matrix/src/layers/*.cpp"
  "matrix/src/pch/*.cpp"
  "matrix/src/platform/api/*.cpp"
  "matrix/src/platform/gui/*.cpp"
  "matrix/src/platform/window/*.cpp"
  "matrix/src/*.cpp"         

  ${GUI_FILES}
)

# library 
add_library(MatrixLib SHARED ${FILES_LIB})

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
  IF (WIN32)
    set(STATIC_GLEW ${STATIC_GLEW} glew32s)
  ELSEIF (UNIX)
    set(STATIC_GLEW ${STATIC_GLEW} libGLEW.a)
  ENDIF ()
  find_package(OpenGL REQUIRED)
  include_directories(${OPENGL_INCLUDE_DIRS})
  set(API_LIB ${API_LIB}
    ${OPENGL_LIBRARIES}
    ${STATIC_GLEW}
  )

ELSEIF (USE_DIRECTX)
  set(API_LIB ${API_LIB}
          
  )
ENDIF ()

target_link_libraries(MatrixLib
  ${API_LIB}
  ${WINDOW_LIB}
  ${Boost_LIBRARIES}
)

set_source_files_properties(matrix/pch/stdafx.cpp
  PROPERTIES
  COMPILE_FLAGS "/Ycstdafx.h"
)