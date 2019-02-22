#ifndef CORE_H
#define CORE_H

#ifdef PLATFORM_WINDOWS_X64
    #ifdef BUILD_DLL
        #define MATRIX_API __declspec(dllexport)
    #else   
        #define MATRIX_API __declspec(dllimport)
    #endif
#else
    #error Matrix only supports Windows x64
#endif

#endif // CORE_H