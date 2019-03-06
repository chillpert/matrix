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

IF (SDL2_ACTIVE) 
# copy dll to exe directory
add_custom_command(TARGET Sandbox POST_BUILD        
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  
        "${PROJECT_SOURCE_DIR}/external/dlls/SDL2.dll"    
        $<TARGET_FILE_DIR:Sandbox>)       
ENDIF()