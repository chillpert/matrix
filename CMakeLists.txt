cmake_minimum_required(VERSION 3.0.0)
set (PROJECT_NAME "Matrix Framework")
project(${PROJECT_NAME} VERSION 0.1.0)

message(${PROJECT_NAME})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(external/include)
include_directories(framework/include)
include_directories(application/include)
link_directories(external/libs)
#link_directories(build/bin/Matrix)
#link_directories(build/bin/Sandbox)

# Macros
IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
ENDIF ()

add_compile_definitions(M_RESOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")

IF (WIN32)
    IF (CMAKE_CL_64)
        add_compile_definitions(PLATFORM_WINDOWS_X64)
        add_compile_definitions(BUILD_DLL)
    ENDIF ()
ENDIF ()

# Files for library
file(GLOB FILES_LIB
    "framework/include/*.h"
    "framework/source/*.cpp"
)

# Library 
add_library(Matrix SHARED ${FILES_LIB} )

target_link_libraries(Matrix
    ${OPENGL_LIBRARIES}
    glew32s
    glfw3
)

set_target_properties(Matrix
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

# Files for executable
file(GLOB FILES_EXE
   
)

# Executable
add_executable(Sandbox application/source/EntryPoint.cpp ${FILES_EXE})

target_link_libraries(Sandbox
    Matrix
)

set_target_properties(Sandbox
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



