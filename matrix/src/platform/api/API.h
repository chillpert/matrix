#ifndef API_H
#define API_H

#ifdef MX_OPENGL_ACTIVE
    #define MX_API_TYPE new MX::API_OpenGL();
#else
    #error "Matrix Framework only supports OpenGL for now"
#endif

#include "matrix/src/pch/stdafx.h"

namespace MX {

    class MX_API API {
    public:
        API() {}
        virtual ~API() {}
    
        virtual bool createContext() const { return false; }
        virtual void update() const {}
        virtual void render() const {}
        virtual void clear() const {}
    };
}

#endif // API_H