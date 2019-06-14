cmake_minimum_required(VERSION 3.0.0)

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

# copy dll to exe directory
IF (USE_SDL2)
  message("Copying SDL2.dll to binary location")

  IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
    file(COPY ${PROJECT_SOURCE_DIR}/external/dlls/SDL2.dll
      DESTINATION ${PROJECT_SOURCE_DIR}/build/bin/debug)

  ELSEIF (CMAKE_BUILD_TYPE STREQUAL "Release")
    file(COPY ${PROJECT_SOURCE_DIR}/external/dlls/SDL2.dll
      DESTINATION ${PROJECT_SOURCE_DIR}/build/bin/release)
    
  ELSEIF (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    file(COPY ${PROJECT_SOURCE_DIR}/external/dlls/SDL2.dll
      DESTINATION ${PROJECT_SOURCE_DIR}/build/bin/relwithbebinfo)

  ELSEIF (CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    file(COPY ${PROJECT_SOURCE_DIR}/external/dlls/SDL2.dll
      DESTINATION ${PROJECT_SOURCE_DIR}/build/bin/minsizerel)
  ENDIF ()
ENDIF()