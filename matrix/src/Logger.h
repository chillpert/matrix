#ifndef LOGGER_H
#define LOGGER_H

#ifdef PLATFORM_WINDOWS_X64
    #ifdef DEBUG
        #define FATAL(x)   Matrix::Logger::p_Fatal(x)
        #define WARN(x)    Matrix::Logger::p_Warn(x)
        #define INFO(x)    Matrix::Logger::p_Info(x)
        #define SUCCESS(x) Matrix::Logger::p_Success(x)

        #include "matrix/src/Core.h"

        #include <string>

        namespace Matrix {

            struct MATRIX_API Logger {
                static std::string getTime();
                static void writeToFile(std::string message);
                static void p_Fatal(std::string message);
                static void p_Warn(std::string message);
                static void p_Info(std::string message);  
                static void p_Success(std::string message);
            };       
        }
    #else
        #define FATAL(x) 
        #define WARN(x) 
        #define INFO(x)
        #define SUCCESS(x)
    #endif
#else   
    #error Debug messages are only available for Windows x64
#endif

#endif // LOGGER_H