cmake_minimum_required(VERSION 3.14.0)
message("MX: Configuring Framework")

# include project files
include_directories(${CMAKE_SOURCE_DIR})

# resource directories
add_compile_definitions(MX_TEXTURE_PATH="${PROJECT_SOURCE_DIR}/resources/textures/")
add_compile_definitions(MX_MODEL_PATH="${PROJECT_SOURCE_DIR}/resources/models/")
add_compile_definitions(MX_SHADER_PATH="${PROJECT_SOURCE_DIR}/resources/shaders/")

####################################################################################################
#############################         windowing         ############################################
####################################################################################################

# glfw
if(USE_GLFW)
  set(GLFW_DIRECTORY glfw)
  
  set(GLFW_INSTALL OFF CACHE STRING "" FORCE)
  set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
  set(GLFW_BUILD_TESTS OFF CACHE STRING "" FORCE)

  add_subdirectory(${PROJECT_SOURCE_DIR}/external/${GLFW_DIRECTORY})
  include_directories(${PROJECT_SOURCE_DIR}/external/${GLFW_DIRECTORY}/include)

  if(WIN32 AND CMAKE_CL_64)
    link_directories(${PROJECT_SOURCE_DIR}/build/external/${GLFW_DIRECTORY}/src)
  endif()

endif(USE_GLFW)

# sdl
if(USE_SDL2)
  set(SDL_DIRECTORY SDL-mirror)

  add_subdirectory(${PROJECT_SOURCE_DIR}/external/${SDL_DIRECTORY})
  include_directories(${PROJECT_SOURCE_DIR}/external/${SDL_DIRECTORY}/include)

  if(WIN32 AND CMAKE_CL_64)
    link_directories(${PROJECT_SOURCE_DIR}/build/external/${SDL_DIRECTORY})
  endif()

endif(USE_SDL2)

# linking
if(USE_GLFW AND USE_SDL2)
  message(FATAL_ERROR "MX: ERROR: You can not use GLFW and SDL2 simultaneously")

elseif(NOT USE_GLFW AND NOT USE_SDL2)
  message(FATAL_ERROR "MX: ERROR: You have to use either SDL2 or GLFW")

elseif(USE_SDL2)
  add_compile_definitions(MX_SDL2_ACTIVE)
  message("MX: Using SDL2")

  if(UNIX)
    set(WINDOW_LIB ${WINDOW_LIB}
      SDL2
    )

  elseif(WIN32 AND CMAKE_CL_64)
    set(WINDOW_LIB ${WINDOW_LIB}
      SDL2d
      )
  
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

####################################################################################################
#############################      rendering API        ############################################
####################################################################################################

# glew
if(USE_OPENGL)
  set(glew-cmake_BUILD_STATIC OFF CACHE STRING "" FORCE)
  set(glew-cmake_BUILD_MULTI_CONTEXT OFF CACHE STRING "" FORCE)
  #set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib CACHE STRING "" FORCE)

  add_subdirectory(${PROJECT_SOURCE_DIR}/external/glew-cmake)
  include_directories(${PROJECT_SOURCE_DIR}/external/glew-cmake/include)
  link_directories(${PROJECT_SOURCE_DIR}/build/lib)

endif(USE_OPENGL)

# linking
if(USE_OPENGL AND USE_DIRECTX)
  message(FATAL_ERROR "MX: ERROR: You can not use OpenGL and DirectX simultaneously")

elseif(NOT USE_OPENGL AND NOT USE_DIRECTX)
  message(FATAL_ERROR "MX: ERROR: You have to use either OpenGL or DirectX")

elseif(USE_DIRECTX)
  message("MX: Using DirectX")
  add_compile_definitions(MX_DIRECTX_ACTIVE)

  set(API_LIB ${API_LIB}
      
  )

elseif(USE_OPENGL)
  message("MX: Using OpenGL")
  add_compile_definitions(MX_OPENGL_ACTIVE)

  if(WIN32)
    set(SHARED_GLEW ${SHARED_GLEW}
      libglew_sharedd
    )
  
  elseif(UNIX)
    set(SHARED_GLEW ${SHARED_GLEW} 
      libglewd.so
    )
  endif()

  find_package(OpenGL REQUIRED)
  include_directories(${OPENGL_INCLUDE_DIRS})

  set(API_LIB ${API_LIB}
    ${OPENGL_LIBRARIES}
    ${SHARED_GLEW}
  )
endif()

####################################################################################################
#############################          boost            ############################################
####################################################################################################

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# boost (windows)
if(WIN32)
  if(CMAKE_CL_64)
    set(BOOST_DIRECTORY boost)

    include_directories(${PROJECT_SOURCE_DIR}/external/${BOOST_DIRECTORY})
    link_directories(${PROJECT_SOURCE_DIR}/external/${BOOST_DIRECTORY})

    set(BOOST_LIB ${Boost_LIBRARIES}
      "libboost_filesystem-vc141-mt-gd-x64-1_70"
      )
  
  endif()
endif()

# boost (unix)
if(UNIX)
  find_package(Boost REQUIRED COMPONENTS filesystem) 
  if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
  endif()

endif()

include_directories(${PROJECT_SOURCE_DIR}/external/boost)

####################################################################################################
#############################           glm             ############################################
####################################################################################################

# glm
include_directories(${PROJECT_SOURCE_DIR}/external/glm)

####################################################################################################
#############################          imgui            ############################################
####################################################################################################

# imgui
include_directories(${PROJECT_SOURCE_DIR}/external/imgui/examples)
include_directories(${PROJECT_SOURCE_DIR}/external/imgui)

if(USE_IMGUI)
  message("MX: Using ImGui")
  add_compile_definitions(MX_IMGUI_ACTIVE)

else()
  message("MX: GUI disabled")
endif()

# imgui implementation files
if(USE_OPENGL)
  set(IMGUI_API ${IMGUI_API}
    "${PROJECT_SOURCE_DIR}/external/imgui/examples/imgui_impl_opengl3.cpp"
  )

elseif(USE_DIRECTX)
  set(IMGUI_API ${IMGUI_API}
    "${PROJECT_SOURCE_DIR}/external/imgui/examples/imgui_impl_dx12.cpp"
  )
ENDIF() 

if(USE_GLFW)
  set(IMGUI_WINDOW ${IMGUI_WINDOW}
    "${PROJECT_SOURCE_DIR}/external/imgui/examples/imgui_impl_glfw.cpp"
  )

elseif(USE_SDL2)
  set(IMGUI_WINDOW ${IMGUI_WINDOW}
    "${PROJECT_SOURCE_DIR}/external/imgui/examples/imgui_impl_sdl.cpp"
  )
ENDIF()

set(IMGUI_FILES ${IMGUI_FILES}
  "${PROJECT_SOURCE_DIR}/external/imgui/*.cpp"
  )

# combine the above
set(GUI_FILES ${GUI_FILES}
  ${IMGUI_FILES}
  ${IMGUI_API}
  ${IMGUI_WINDOW}
  )

####################################################################################################
#############################        stb image          ############################################
####################################################################################################

# stb_image
include_directories(${PROJECT_SOURCE_DIR}/external/stb_image)

####################################################################################################
#############################    MatrixLib logging      ############################################
####################################################################################################

# logging
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions(MX_DEBUG)
endif()

# log window events
if(LOG_WINDOW_EVENTS)
  message("MX: Logging events enabled")
  add_compile_definitions(MX_LOG_EVENTS)
endif()

####################################################################################################
###########################    MatrixLib dll generation   ##########################################
####################################################################################################

if(WIN32 AND CMAKE_CL_64)
  # declspec (windows)
  add_compile_definitions(MX_BUILD_DLL)
  add_compile_definitions(MX_PLATFORM_WINDOWS_X64)

elseif(UNIX)
    # declspec (unix)
    add_compile_definitions(MX_BUILD_DLL)
    add_compile_definitions(MX_PLATFORM_UNIX_X64)

endif()

# files for library
file(GLOB FILES_LIB
  "${PROJECT_SOURCE_DIR}/matrix/src/controller/*.cpp"
  "${PROJECT_SOURCE_DIR}/matrix/src/event/*.cpp"
  "${PROJECT_SOURCE_DIR}/matrix/src/layers/*.cpp"
  "${PROJECT_SOURCE_DIR}/matrix/src/pch/*.cpp"
  "${PROJECT_SOURCE_DIR}/matrix/src/platform/api/*.cpp"
  "${PROJECT_SOURCE_DIR}/matrix/src/platform/gui/*.cpp"
  "${PROJECT_SOURCE_DIR}/matrix/src/platform/window/*.cpp"
  "${PROJECT_SOURCE_DIR}/matrix/src/*.cpp" 
  )

file(GLOB GUI_FILES_NON_PCH
  ${GUI_FILES}
)

# precompiled header
if(MSVC)
  set_source_files_properties(${PROJECT_SOURCE_DIR}/matrix/src/pch/stdafx.cpp
    PROPERTIES
    COMPILE_FLAGS "/Ycstdafx.h"
    )
  foreach(src_file ${FILES_LIB})
    set_source_files_properties(
      ${src_file}
      PROPERTIES
      COMPILE_FLAGS "/Yustdafx.h"
      )
  endforeach(src_file ${FILES_LIB})
  list(APPEND FILES_LIB ${PROJECT_SOURCE_DIR}/matrix/src/pch/stdafx.cpp)

else()
  message("MX: WARN: No PCH available for current compiler")

endif()

# library
add_library(MatrixLib SHARED ${FILES_LIB} ${GUI_FILES_NON_PCH})

target_link_libraries(MatrixLib
  ${API_LIB}
  ${WINDOW_LIB}
  ${Boost_LIBRARIES}
  )

# controller profile
add_compile_definitions(MX_DEFAULT_CONTROLLER)