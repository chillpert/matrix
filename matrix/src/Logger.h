#ifndef LOGGER_H
#define LOGGER_H

#ifdef MX_DEBUG
    #define MX_FATAL(x)   Matrix::Logger::p_Fatal(x)
    #define MX_WARN(x)    Matrix::Logger::p_Warn(x)
    #define MX_INFO(x)    Matrix::Logger::p_Info(x)
    #define MX_SUCCESS(x) Matrix::Logger::p_Success(x)
#else
    #define MX_FATAL(x) 
    #define MX_WARN(x) 
    #define MX_INFO(x)
    #define MX_SUCCESS(x)
#endif

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

#endif // LOGGER_H