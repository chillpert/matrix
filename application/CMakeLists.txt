cmake_minimum_required(VERSION 3.14.0)

message("MX: Configuring Application")

# include headers
include_directories(application/src)

# all implementation files
file(GLOB FILES_EXE
   
  )

# create executable
add_executable(Sandbox application/src/EntryPoint.cpp ${FILES_EXE})

# link against Matrix Framework
target_link_libraries(Sandbox
  MatrixLib
  )

# configure output directories
set_target_properties(MatrixLib Sandbox
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

# copy sdl2.dll to binary location in post build
if(NOT UNIX)
  message("MX: Copying SDL2.dll to binary location")

  add_custom_command(
    TARGET Sandbox
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/build/external/SDL-mirror/SDL2d.dll
            ${PROJECT_SOURCE_DIR}/build/bin/${BUILD_PATH}/SDL2d.dll
    COMMENT "Running POST_BUILD action: Copying SDL2d.dll to binary location"
    )
endif()

# copy glewd.dll to binary location in post build
if(USE_OPENGL AND NOT UNIX)
  message("MX: Copying glewd.dll to binary location")

  add_custom_command(
    TARGET Sandbox
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/build/bin/glewd.dll
            ${PROJECT_SOURCE_DIR}/build/bin/${BUILD_PATH}/glewd.dll
    COMMENT "Running POST_BUILD action: Copying glewd.dll to binary location"
    )
endif()