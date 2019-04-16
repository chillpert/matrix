#ifndef MODEL_WAVEFRONT_H
#define MODEL_WAVEFRONT_H

#include "matrix/src/pch/stdafx.h"
#include "matrix/src/platform/api/Model.h"
#include "matrix/src/platform/api/Model_OpenGL.h"
#include "matrix/src/platform/api/Model_DirectX.h"

namespace MX {

    // parse wavefront files (.obj)
    class Wavefront_Parser {
    public:    
        MX_API Wavefront_Parser(MX_MODEL_API &model);
        MX_API ~Wavefront_Parser() {}

        MX_API void start();

        // parse string to one floats
        MX_API float split_1f(std::string &line);
        // parse string to two floats
        MX_API glm::vec2 split_2f(std::string &line);
        // parse string to three floats
        MX_API glm::vec3 split_3f(std::string &line);

        // parse line of format "f v v v" 
        MX_API std::vector<unsigned int> &f_description_1(std::string &line);

        MX_API std::vector<std::string> split_face(std::string &line);
        // finds out the way of face description and returns an integer respectively
        MX_API int get_face_description(std::string &line);
    private:
        MX_MODEL_API *m_Model;

        // temporary vectors for vertices
        std::vector<glm::vec3> temp_V;
        std::vector<glm::vec2> temp_Vt;
        std::vector<glm::vec3> temp_Vn;
        // temporary vectors for faces
        std::vector<unsigned int> temp_f_V;
        std::vector<unsigned int> temp_f_Vt;
        std::vector<unsigned int> temp_f_Vn;
    };
}

#endif // MODEL_WAVEFRONT_H
