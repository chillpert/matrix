cmake_minimum_required(VERSION 3.14.4)
message("MX: Configuring Framework")

# glfw
if(USE_GLFW)
  set(GLFW_DIRECTORY glfw)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLFW_DIRECTORY}/include)
  
  set(GLFW_INSTALL OFF CACHE STRING "" FORCE)
  set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
  set(GLFW_BUILD_TESTS OFF CACHE STRING "" FORCE)
  
  add_subdirectory(${PROJECT_SOURCE_DIR}/external/${GLFW_DIRECTORY})
  include_directories(${PROJECT_SOURCE_DIR}/external/${GLFW_DIRECTORY}/include)

endif(USE_GLFW)

if(USE_OPENGL)
  # glew
  set(glew-cmake_BUILD_STATIC OFF CACHE STRING "" FORCE)
  set(glew-cmake_BUILD_MULTI_CONTEXT OFF CACHE STRING "" FORCE)

  add_subdirectory(${PROJECT_SOURCE_DIR}/external/glew-cmake)
  include_directories(${PROJECT_SOURCE_DIR}/external/glew-cmake/include)
  link_directories(${PROJECT_SOURCE_DIR}/build/lib)

endif(USE_OPENGL)


# operating system
if(WIN32)
  if(CMAKE_CL_64)
    # declspec (windows)
    add_compile_definitions(MX_BUILD_DLL)
    add_compile_definitions(MX_PLATFORM_WINDOWS_X64)

    # boost (windows)
    set(BOOST_LIB ${Boost_LIBRARIES}
      "libboost_filesystem-vc141-mt-gd-x64-1_70"
      )
  endif()
elseif(UNIX)
    # declspec (unix)
    add_compile_definitions(MX_BUILD_DLL)
    add_compile_definitions(MX_PLATFORM_UNIX_X64)

    # boost (unix)
    find_package(Boost REQUIRED COMPONENTS filesystem) 
    if(Boost_FOUND)
      include_directories(${Boost_INCLUDE_DIRS}) 
    endif()

endif()

# rendering api
if(USE_OPENGL AND USE_DIRECTX)
  message(FATAL_ERROR "MX: ERROR: You can not use OpenGL and DirectX simultaneously")

elseif(NOT USE_OPENGL AND NOT USE_DIRECTX)
  message(FATAL_ERROR "MX: ERROR: You have to use either OpenGL or DirectX")

elseif(USE_DIRECTX)
  message("MX: Using DirectX")
  add_compile_definitions(MX_DIRECTX_ACTIVE)

  # prepare for linking
  set(API_LIB ${API_LIB}
          
  )

elseif(USE_OPENGL)
  message("MX: Using OpenGL")
  add_compile_definitions(MX_OPENGL_ACTIVE)

  # prepare for static linking
  if(WIN32)
    set(STATIC_GLEW ${STATIC_GLEW}
      glew32s
    )
  
  elseif(UNIX)
    set(STATIC_GLEW ${STATIC_GLEW} 
      libglewd.so
    )
  endif()

  find_package(OpenGL REQUIRED)
  include_directories(${OPENGL_INCLUDE_DIRS})

  set(API_LIB ${API_LIB}
    ${OPENGL_LIBRARIES}
    ${STATIC_GLEW}
  )
endif()

# windowing
if(USE_GLFW AND USE_SDL2)
  message(FATAL_ERROR "MX: ERROR: You can not use GLFW and SDL2 simultaneously")

elseif(NOT USE_GLFW AND NOT USE_SDL2)
  message(FATAL_ERROR "MX: ERROR: You have to use either SDL2 or GLFW")

elseif(USE_SDL2)
  add_compile_definitions(MX_SDL2_ACTIVE)
  message("MX: Using SDL2")

  # set library for linking
  set(WINDOW_LIB ${WINDOW_LIB}   
    SDL2
  )

  if(UNIX)
    #find_package(SDL2_REQUIRED)
    #include_directories(${SDL2_INCLUDE_DIRS})
  endif()

elseif(USE_GLFW)
  message("MX: Using GLFW")
  add_compile_definitions(MX_GLFW_ACTIVE)

  # set library for linking
  set(WINDOW_LIB ${WINDOW_LIB}
    glfw3
    ${GLFW_LIBRARIES}
  )
endif()

# include and link directories
include_directories(${CMAKE_SOURCE_DIR})
include_directories(external/include)
link_directories(external/libs)

# boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# logging
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions(MX_DEBUG)
endif()

# log window events
if(LOG_WINDOW_EVENTS)
  message("MX: Logging events enabled")
  add_compile_definitions(MX_LOG_EVENTS)
endif()

# controller
add_compile_definitions(MX_DEFAULT_CONTROLLER)

# gui
if(USE_IMGUI)
  message("MX: Using ImGui")
  add_compile_definitions(MX_IMGUI_ACTIVE)

else()
  message("MX: GUI disabled")
endif()

# precompiled header
if(MSCV)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
else()
  message("MX: WARN: No PCH available for current compiler")
endif()

# IMGUI
if(USE_OPENGL)
  set(IMGUI_API ${IMGUI_API}
    "external/include/IMGUI/imgui_impl_opengl3.cpp"
  )

elseif(USE_DIRECTX)
  set(IMGUI_API ${IMGUI_API}
  
  )
ENDIF() 

if(USE_GLFW)
  set(IMGUI_WINDOW ${IMGUI_WINDOW}
    "external/include/IMGUI/imgui_impl_glfw.cpp"
  )

elseif(USE_SDL2)
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

# combine the above
if(USE_IMGUI)
  set(GUI_FILES ${GUI_FILES}
    ${IMGUI_FILES}
    ${IMGUI_API}
    ${IMGUI_WINDOW}
  )

else()
  set(GUI_FILES ${GUI_FILES})
endif()

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

target_link_libraries(MatrixLib
  ${API_LIB}
  ${WINDOW_LIB}
  ${Boost_LIBRARIES}
  )

set_source_files_properties(matrix/pch/stdafx.cpp
  PROPERTIES
  COMPILE_FLAGS "/Ycstdafx.h"
  )

# resource directories
add_compile_definitions(MX_TEXTURE_PATH="${PROJECT_SOURCE_DIR}/resources/textures/")
add_compile_definitions(MX_MODEL_PATH="${PROJECT_SOURCE_DIR}/resources/models/")
add_compile_definitions(MX_SHADER_PATH="${PROJECT_SOURCE_DIR}/resources/shaders/")