#ifndef API_H
#define API_H

#ifdef MX_OPENGL_ACTIVE
    #define API_TYPE new Matrix::API_OpenGL();
#else
    #error "Matrix Framework only supports OpenGL for now"
#endif

#include "matrix/src/pch/stdafx.h"

namespace Matrix {

    class MATRIX_API API {
    public:
        API() {}
        ~API() {}
    
        virtual bool createContext() const { return false; }
        virtual void render() const {}
    };
}

#endif // API_H