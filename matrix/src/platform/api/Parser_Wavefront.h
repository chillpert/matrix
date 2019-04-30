#ifndef MODEL_WAVEFRONT_H
#define MODEL_WAVEFRONT_H

#include "matrix/src/pch/stdafx.h"
#include "matrix/src/platform/api/Model.h"
#include "matrix/src/platform/api/Model_OpenGL.h"
#include "matrix/src/platform/api/Model_DirectX.h"

namespace MX
{

  // all supported descriptions of data inside wavefront files
  enum Wavefront_Description
  {
    Error = 0,
    V = 1, 
    V_VT = 2,
    V_VN = 3,
    V_VN_VT = 4
  };

  struct Wavefront_Config
  {
    MX_API Wavefront_Config() 
        : hasV(0), hasVn(0), hasVt(0), faces_1(0), faces_2(0), faces_3(0), faces_4(0) {}
    MX_API ~Wavefront_Config() {}

    // returns all values of the members of this struct
    MX_API std::string toString(const std::string &path);

    bool hasV, hasVn, hasVt;
    // f v v v
    bool faces_1;
    // f v/vt v/vt v/vt
    bool faces_2;
    // f v//vn v//vn v//vn
    bool faces_3;
    // f v/vt/vn v/vt/vn v/vt/vn
    bool faces_4;
  };                                                                       

  // parses wavefront files (.obj)
  class Wavefront_Parser
  {
  public:    
    MX_API Wavefront_Parser(MX_MODEL &model);
    MX_API ~Wavefront_Parser() {}

    MX_API void start();
    // parse file to check what data it contains
    
    // split face into substrings
    MX_API std::vector<std::string> split_face(std::string &line);

    // parse string to 1, 2 or 3 floats respectively
    MX_API glm::vec1 split_1f(std::string &line);
    MX_API glm::vec2 split_2f(std::string &line);
    MX_API glm::vec3 split_3f(std::string &line);

    // parse faces data
    MX_API void parse_faces(std::string &line, Wavefront_Description description);
    
    // returns the length of all the temporary vectors
    MX_API std::string toString();
  private:
    MX_MODEL *m_Model;

    // temporary vectors for vertices
    std::vector<glm::vec3> temp_V;
    std::vector<glm::vec2> temp_Vt;
    std::vector<glm::vec3> temp_Vn;
    // temporary vectors for faces
    std::vector<unsigned int> temp_f_V;
    std::vector<unsigned int> temp_f_Vt;
    std::vector<unsigned int> temp_f_Vn;

    Wavefront_Config config;
  };   
}

#endif // MODEL_WAVEFRONT_H
