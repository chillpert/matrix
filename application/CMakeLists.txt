cmake_minimum_required(VERSION 3.14.0)

message("MX: Configuring Application")

# this file is used to configure your actual application
# make sure the Matrix.dll file is in the same directory
# as your executable

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

# copy sdl2.dll to binary location
if(USE_SDL2)
  message("MX: Copying SDL2.dll to binary location")

  set(SDL2_DLL_PATH ${PROJECT_SOURCE_DIR}/build/external/SDL-mirror/SDL2d.dll)

  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    file(COPY ${SDL2_DLL_PATH}
      DESTINATION ${PROJECT_SOURCE_DIR}/build/bin/debug)

  elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    file(COPY ${SDL2_DLL_PATH}
      DESTINATION ${PROJECT_SOURCE_DIR}/build/bin/release)
    
  elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    file(COPY ${SDL2_DLL_PATH}
      DESTINATION ${PROJECT_SOURCE_DIR}/build/bin/relwithbebinfo)

  elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    file(COPY ${SDL2_DLL_PATH}
      DESTINATION ${PROJECT_SOURCE_DIR}/build/bin/minsizerel)
  endif()
endif(USE_SDL2)

# copy glewd.dll to binary location
if(USE_OPENGL AND WIN32 AND CMAKE_CL_64)
  message("MX: Copying glewd.dll to binary location")

  set(GLEWD_DLL_PATH ${PROJECT_SOURCE_DIR}/build/bin/glewd.dll)

  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    file(COPY ${GLEWD_DLL_PATH}
      DESTINATION ${PROJECT_SOURCE_DIR}/build/bin/debug)

  elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    file(COPY ${GLEWD_DLL_PATH}
      DESTINATION ${PROJECT_SOURCE_DIR}/build/bin/release)
    
  elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    file(COPY ${GLEWD_DLL_PATH}
      DESTINATION ${PROJECT_SOURCE_DIR}/build/bin/relwithbebinfo)

  elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    file(COPY ${GLEWD_DLL_PATH}
      DESTINATION ${PROJECT_SOURCE_DIR}/build/bin/minsizerel)
  endif()
endif(USE_OPENGL)