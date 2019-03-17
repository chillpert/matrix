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
    Matrix
)

# configure output directories
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

# copy dll to exe directory
IF (USE_SDL2) 
    message("Copying SDL2.dll to binary location")
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/external/dlls/SDL2.dll
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/bin/debug)
ENDIF()