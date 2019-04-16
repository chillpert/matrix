#include "matrix/src/platform/api/Parser_Wavefront.h"

namespace MX {

    Wavefront_Parser::Wavefront_Parser(MX_MODEL_API &model) {
        m_Model = &model;
    }

    void Wavefront_Parser::start() {
        MX_INFO("MX: Model: Wavefront Parser: started");
        std::ifstream file(m_Model->getPath());

        bool toggle_face_description = 1;
        int face_description = 0;
        
        std::string line;
        while (std::getline(file, line)) {

            if (line.length() > 2) {

                if (line.at(0) == 'v' || line.at(0) == 'V') {
                    // vt
                    if (line.at(1) == 't' || line.at(1) == 'T') {
                        temp_Vt.push_back(split_2f(line));
                    } 
                    // vn
                    else if (line.at(1) == 'n' || line.at(1) == 'N') {
                        temp_Vn.push_back(split_3f(line));
                    }
                    // v
                    else {
                        temp_V.push_back(split_3f(line));
                    }
                } 
                // f
                else if (line.at(0) == 'f' || line.at(0) == 'F') {

                    if (toggle_face_description) {
                        face_description = get_face_description(line);
                        toggle_face_description = 0;
                    }
                    // f v v v
                    if (face_description == 1) {
                        std::vector<unsigned int> f_v(f_description_1(line));
                        for (auto &it : f_v) 
                            temp_f_V.push_back(it);
                    } 
                    // f v/vt v/vt v/vt
                    else if (face_description == 2) {

                    } 
                    // f v//vn v//vn v//vn
                    else if (face_description == 3) {

                    } 
                    // f v/vt/vn v/vt/vn v/vt/vn
                    else if (face_description == 4) {

                    } else {
                        MX_FATAL("MX: Model: Wavefront Parser: Face description not supported");
                    }
                } 
                // s
                else if (line.at(0) == 's' || line.at(0) == 'S') {
                    
                }
                // mtllib
                else if (line.find("mtllib")) {

                }
                // usemtl
                else if (line.find("usemtl")) {

                }
                // any other line than a comment
                else if (line.at(0) != '#'){
                    MX_WARN("MX: Model: Wavefront Parser: Unkown description: " + line + "\n");
                }
            }
        }

        MX_INFO("MX: temp_V: " + std::to_string(temp_V.size()));
        MX_INFO("MX: temp_Vt: " + std::to_string(temp_Vt.size()));
        MX_INFO("MX: temp_Vn: " + std::to_string(temp_Vn.size()));
        MX_INFO("MX: temp_f_V: " + std::to_string(temp_f_V.size()));
        MX_INFO("MX: temp_f_Vt: " + std::to_string(temp_f_Vt.size()));
        MX_INFO("MX: temp_f_Vn: " + std::to_string(temp_f_Vn.size()));
        
        for (unsigned int i = 0; i < temp_f_V.size(); i++) {
            
        }
    }

    glm::vec2 Wavefront_Parser::split_2f(std::string &line) {
        std::istringstream iss(line);
        std::vector<float> temp;
        do {
            std::string subs;
            iss >> subs;
            temp.push_back(::atof(subs.c_str()));
        } while (iss);
        
        return {temp.at(1), temp.at(2)};
    }

    glm::vec3 Wavefront_Parser::split_3f(std::string &line) {
        std::istringstream iss(line);
        std::vector<float> temp;
        do {
            std::string subs;
            iss >> subs;
            temp.push_back(::atof(subs.c_str()));
        } while (iss);
        
        return {temp.at(1), temp.at(2), temp.at(3)};
    }

    float Wavefront_Parser::split_1f(std::string &line) {
        std::istringstream iss(line);
        std::vector<float> temp;
        do {
            std::string subs;
            iss >> subs;
            temp.push_back(::atof(subs.c_str()));
        } while (iss);
    
        return temp.at(1);
    }

    std::vector<std::string> Wavefront_Parser::split_face(std::string &line) {
        std::istringstream buf(line);
    
        std::istream_iterator<std::string> beg(buf), end;
        std::vector<std::string> tokens(beg, end);

        return tokens;
    }

    // parse line of format "f v v v"
    std::vector<unsigned int> &Wavefront_Parser::f_description_1(std::string &line) {
        std::vector<unsigned int> f_V;
        
        std::stringstream ss;
        ss << line;

        std::string temp;
        int found;

        while (!ss.eof()) {
            ss >> temp;
            if (std::stringstream(temp) >> found)
                f_V.push_back(found);

            temp = "";
        }

        for (auto &it : f_V) 
            MX_FATAL(std::to_string(it) + " ");
        std::cout << "\n";

        return f_V;
    }

    // finds out the way of face description and returns an integer respectively
    // return 1 - f v v v
    // return 2 - f v/vt v/vt v/vt
    // return 3 - f v//vn v//vn v//vn
    // return 4 - f v/vt/vn v/vt/vn v/vt/vn
    int Wavefront_Parser::get_face_description(std::string &line) {
        // stores amount of forward slashes
        __int64 n = std::count(line.begin(), line.end(), '/');
        size_t found = 0;

        switch (n) {
            case 0: 
                return 1;
                break;
            case 3:
                return 2;
                break;
            case 6: 
                found = line.find('/');
                if (line.at(found + 1) == '/') {
                    return 3;
                }
                return 4;
                break;
            default:
                return 0;
                break;
        }
    }

}