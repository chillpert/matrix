cmake_minimum_required(VERSION 3.14.0)

message("MX: Configuring Shadow Mapping Test")

# include headers
include_directories("renderer/shadow mapping")

# all implementation files
file(GLOB FILES_EXE
   
  )

# create executable
add_executable(ShadowMapping "renderer/shadow mapping/main.cpp" ${FILES_EXE})

# link against Matrix Framework
target_link_libraries(ShadowMapping
  MatrixLib
  )

# configure output directories
set_target_properties(MatrixLib ShadowMapping
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/build/lib/debug"
  LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/build/lib/debug"
  RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/build/bin/debug"

  ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/build/lib/release"
  LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/build/lib/release"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/build/bin/release"

  ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${PROJECT_SOURCE_DIR}/build/lib/minsizerel"
  LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${PROJECT_SOURCE_DIR}/build/lib/minsizerel"
  RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${PROJECT_SOURCE_DIR}/build/bin/minsizerel"   

  ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PROJECT_SOURCE_DIR}/build/lib/relwithbebinfo"
  LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PROJECT_SOURCE_DIR}/build/lib/relwithbebinfo"
  RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PROJECT_SOURCE_DIR}/build/bin/relwithbebinfo"
  )

# set build paths
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(BUILD_PATH debug)

elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(BUILD_PATH release)
  
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
  set(BUILD_PATH relwithbebinfo)

elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
  set(BUILD_PATH minsizerel)

endif()

## copy dlls to binary location in post build
if(NOT UNIX)
  message("MX: Copying SDL2.dll to binary location")

  add_custom_command(
    TARGET ShadowMapping
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/build/external/SDL-mirror/${SDL_BUILD_PATH}/SDL2d.dll
            ${PROJECT_SOURCE_DIR}/build/bin/${BUILD_PATH}/SDL2d.dll
    COMMENT "Running POST_BUILD action: Copying SDL2d.dll to binary location"
    )
endif()

## copy dlls to binary location in post build
if(USE_OPENGL AND WIN32 AND CMAKE_CL_64)
  message("MX: Copying assimp-vc142-mtd.dll to binary location")

  add_custom_command(
    TARGET ShadowMapping
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/build/external/assimp/code/${ASSIMP_BUILD_PATH}/assimp-vc142-mtd.dll
            ${PROJECT_SOURCE_DIR}/build/bin/${BUILD_PATH}/assimp-vc142-mtd.dll
  )
endif()