cmake_minimum_required(VERSION 3.14.0)
message("MX: Configuring Framework")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(LIB_PATH Debug)

elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(LIB_PATH Release)
  
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
  set(LIB_PATH RelWithDebInfo)

elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
  set(LIB_PATH MinSizeRel)
endif()

# include project files
include_directories(${CMAKE_SOURCE_DIR}/matrix)
include_directories(${CMAKE_SOURCE_DIR}/matrix/src)
include_directories(${CMAKE_SOURCE_DIR}/matrix/src/pch)
include_directories(${CMAKE_SOURCE_DIR}/matrix/src/controller)
include_directories(${CMAKE_SOURCE_DIR}/matrix/src/event)
include_directories(${CMAKE_SOURCE_DIR}/matrix/src/layers)
include_directories(${CMAKE_SOURCE_DIR}/matrix/src/platform/api)
include_directories(${CMAKE_SOURCE_DIR}/matrix/src/platform/gui)
include_directories(${CMAKE_SOURCE_DIR}/matrix/src/platform/gui/utility)
include_directories(${CMAKE_SOURCE_DIR}/matrix/src/platform/gui/editor)
include_directories(${CMAKE_SOURCE_DIR}/matrix/src/platform/gui/editor/legacy)
include_directories(${CMAKE_SOURCE_DIR}/matrix/src/platform/window)
include_directories(${CMAKE_SOURCE_DIR}/matrix/src/intersections)
include_directories(${CMAKE_SOURCE_DIR}/matrix/src/math)

# resource directories
add_compile_definitions(MX_RESOURCES="${PROJECT_SOURCE_DIR}/resources/")
add_compile_definitions(MX_TEXTURE_PATH="${PROJECT_SOURCE_DIR}/resources/textures/")
add_compile_definitions(MX_MODEL_PATH="${PROJECT_SOURCE_DIR}/resources/models/")
add_compile_definitions(MX_SHADER_PATH="${PROJECT_SOURCE_DIR}/resources/shaders/")
add_compile_definitions(MX_SCENES_PATH="${PROJECT_SOURCE_DIR}/resources/scenes/")
add_compile_definitions(MX_FONTS_PATH="${PROJECT_SOURCE_DIR}/external/imgui/misc/fonts/")
add_compile_definitions(MX_IMGUI_DEFAULT_INI_PATH="${PROJECT_SOURCE_DIR}/resources/imgui_init/")
add_compile_definitions(MX_ICONS_PATH="${PROJECT_SOURCE_DIR}/matrix/src/platform/gui/icons/")

####################################################################################################
#############################         windowing         ############################################
####################################################################################################

# sdl
set(SDL_DIRECTORY SDL-mirror)

add_subdirectory(${PROJECT_SOURCE_DIR}/external/${SDL_DIRECTORY})
include_directories(${PROJECT_SOURCE_DIR}/external/${SDL_DIRECTORY}/include)

if(WIN32 AND CMAKE_CL_64)
  link_directories(${PROJECT_SOURCE_DIR}/build/external/${SDL_DIRECTORY}/${LIB_PATH})
endif()

# sdl image
if(UNIX)
  INCLUDE(FindPkgConfig)

  PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
  PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
elseif(WIN32 AND CMAKE_CL_64)

endif()

include_directories(${PROJECT_SOURCE_DIR}/external/SDL-image)

# linking
if(UNIX)
  set(WINDOW_LIB ${WINDOW_LIB}
    SDL2
    ${SDL2IMAGE_LIBRARIES}
  )

elseif(WIN32 AND CMAKE_CL_64)
  set(WINDOW_LIB ${WINDOW_LIB}
    SDL2d
  )
endif()

####################################################################################################
#############################      model loading        ############################################
####################################################################################################

# assimp
set(ASSIMP_DIRECTORY assimp)

set(BUILD_FRAMEWORK OFF CACHE STRING "" FORCE)
set(ASSIMP_DOUBLE_PRECISION OFF CACHE STRING "" FORCE)
set(ASSIMP_OPT_BUILD_PACKAGES OFF CACHE STRING "" FORCE)
set(ASSIMP_ANDROID_JNIIOSYSTEM OFF CACHE STRING "" FORCE)
set(ASSIMP_NO_EXPORT OFF CACHE STRING "" FORCE)
set(ASSIMP_BUILD_ZLIB OFF CACHE STRING "" FORCE)
set(ASSIMP_BUILD_SAMPLES OFF CACHE STRING "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE STRING "" FORCE)
set(ASSIMP_COVERALLS OFF CACHE STRING "" FORCE)
set(ASSIMP_ASAN OFF CACHE STRING "" FORCE)
set(ASSIMP_UBSAN OFF CACHE STRING "" FORCE)
set(SYSTEM_IRRXML OFF CACHE STRING "" FORCE)
set(BUILD_DOCS OFF CACHE STRING "" FORCE)
set(IGNORE_GIT_HASH OFF CACHE STRING "" FORCE)

add_subdirectory(${PROJECT_SOURCE_DIR}/external/${ASSIMP_DIRECTORY})
include_directories(
  ${PROJECT_SOURCE_DIR}/external/${ASSIMP_DIRECTORY}/include 
  ${PROJECT_SOURCE_DIR}/build/external/${ASSIMP_DIRECTORY}/include
  )

if(UNIX)
  link_directories(${PROJECT_SOURCE_DIR}/build/external/${ASSIMP_DIRECTORY}/code)
elseif(WIN32 AND CMAKE_CL_64)
  link_directories(${PROJECT_SOURCE_DIR}/build/external/${ASSIMP_DIRECTORY}/code/${LIB_PATH})
else()
  message("MX: Assimp: no linking directory defined for your operating system")
endif()

if(UNIX)
  set(MODEL_LOADING_LIB ${MODEL_LOADING_LIB}
    libassimpd.so
  )
elseif(WIN32 AND CMAKE_CL_64)
  set(MODEL_LOADING_LIB ${MODEL_LOADING_LIB}
    assimp-vc142-mtd
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

if(UNIX)
  link_directories(${PROJECT_SOURCE_DIR}/build/lib)
elseif(WIN32 AND CMAKE_CL_64)
  link_directories(${PROJECT_SOURCE_DIR}/build/lib/${LIB_PATH})
else()
  message("MX: Glew: no linking directory defined for your operating system")
endif()

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

  message("MX: Linking Glew")
  if(WIN32)
    set(SHARED_GLEW ${SHARED_GLEW}
      "libglew_sharedd"
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

set(BOOST_DIRECTORY boost)

# boost (windows)
if(WIN32)
  if(CMAKE_CL_64)
    set(BOOST_DIRECTORY boost)

    include_directories(${PROJECT_SOURCE_DIR}/external/${BOOST_DIRECTORY})
    link_directories(${PROJECT_SOURCE_DIR}/external/${BOOST_DIRECTORY})

    set(BOOST_LIB ${BOOST_LIB}
      "libboost_filesystem-vc142-mt-gd-x64-1_71"
      )
  
  endif()

# boost (unix)
elseif(UNIX)
  find_package(Boost REQUIRED COMPONENTS filesystem) 
  if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    
    set(BOOST_LIB ${Boost_LIBRARIES}
      ${Boost_LIBRARIES}
      )

  endif()

endif()

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

if(GUI_LOG_ALL)
  add_compile_definitions(MX_GUI_LOG_ALL)
endif()

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

set(IMGUI_WINDOW ${IMGUI_WINDOW}
  "${PROJECT_SOURCE_DIR}/external/imgui/examples/imgui_impl_sdl.cpp"
)

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
  "${PROJECT_SOURCE_DIR}/matrix/src/platform/gui/utility/*.cpp"
  "${PROJECT_SOURCE_DIR}/matrix/src/platform/gui/editor/*.cpp"
  "${PROJECT_SOURCE_DIR}/matrix/src/platform/gui/editor/legacy/*.cpp"
  "${PROJECT_SOURCE_DIR}/matrix/src/platform/window/*.cpp"
  "${PROJECT_SOURCE_DIR}/matrix/src/intersections/*.cpp"
  "${PROJECT_SOURCE_DIR}/matrix/src/math/*.cpp" 
  "${PROJECT_SOURCE_DIR}/matrix/src/*.cpp"
  )

file(GLOB GUI_FILES_NON_PCH
  ${GUI_FILES}
)

# precompiled header currently disabled for all platform
if(NOT)
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
  ${BOOST_LIB}
  ${MODEL_LOADING_LIB}
  )

# controller profile
add_compile_definitions(MX_DEFAULT_CONTROLLER)