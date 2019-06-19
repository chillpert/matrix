#include <Parser_Wavefront.h>

namespace MX
{
  Wavefront_Parser::Wavefront_Parser(MX_MODEL &model)
  {
    m_Model = &model;
  }

  void Wavefront_Parser::start()
  {
    MX_INFO("MX: Model: Wavefront Parser: started");
    
    bool V_VN_VT_flag = 0;
    
    if (/*description != Error*/1)
    {
      std::ifstream file(m_Model->m_Path);
      std::string line;

      while (std::getline(file, line)) {

        if (line.length() > 2)
        {
          if (line.at(0) == 'v')
          {
            // vt
            if (line.at(1) == 't') 
              temp_Vt.push_back(split_2f(line)); 
            // vn
            else if (line.at(1) == 'n') 
              temp_Vn.push_back(split_3f(line));
            // v
            else 
              temp_V.push_back(split_3f(line));
          } 
          // f
          else if (line.at(0) == 'f')
          {
            Wavefront_Description description2 = V_VN_VT;

            if (!V_VN_VT_flag)
            {
              std::smatch matches;
              std::regex reg_v_vn_vt("(f ([0-9]+/[0-9]+/[0-9]+) ([0-9]+/[0-9]+/[0-9]+) ([0-9]+/[0-9]+/[0-9]+)$)");
              if (std::regex_search(line, matches, reg_v_vn_vt))
              {
                description2 = V_VN_VT;
                V_VN_VT_flag = 1;
              } 
            }

            parse_faces(line, description2);
          }

          // any other line than a comment
          else if (line.at(0) != '#') 
            MX_WARN("MX: Model: Wavefront Parser: Can not parse: \"" + line + "\"");
        }
      }

      //MX_FATAL("Test" + std::to_string(debug_counter));

      //MX_INFO(toString());

      for (unsigned int i = 0; i < temp_f_V.size(); i++) {
        unsigned int vertexIndex = temp_f_V.at(i);
        unsigned int textureIndex = temp_f_Vt.at(i);
        unsigned int normalIndex = temp_f_Vn.at(i);

        glm::vec3 vertex = temp_V.at(vertexIndex - 1);
        glm::vec2 texture = temp_Vt.at(textureIndex - 1);
        glm::vec3 normal = temp_Vn.at(normalIndex - 1);

        m_Model->m_V.push_back(vertex);
        m_Model->m_Vt.push_back(texture);
        m_Model->m_Vn.push_back(normal);
      }

    }

    else
    {
      MX_FATAL("MX: Model: Wavefront Parser: Error in file format");
    }

    MX_SUCCESS("MX: Model: Wavefront Parser: Completed");
  }

  std::string Wavefront_Parser::toString()
  {
    std::string message =
      "\nMX: Model: Object at " + m_Model->m_Path           + "\n" +
      "\ttemp_V: "      + std::to_string(temp_V.size())     + "\n" +
      "\ttemp_Vt: "     + std::to_string(temp_Vt.size())    + "\n" +  
      "\ttemp_Vn: "     + std::to_string(temp_Vn.size())    + "\n" +
      "\ttemp_f_V: "    + std::to_string(temp_f_V.size())   + "\n" +
      "\ttemp_f_Vt: "   + std::to_string(temp_f_Vt.size())  + "\n" +
      "\ttemp_f_Vn: "   + std::to_string(temp_f_Vn.size())  + "\n";
    return message;
  }

  std::string Wavefront_Config::toString(const std::string &path)
  {
    std::string message =    
      "\nMX: Model: Object at " + path              + "\n" +
      "\tHasV: "        + std::to_string(hasV)      + "\n" +
      "\tHasVn: "       + std::to_string(hasVn)     + "\n" +
      "\tHasVt: "       + std::to_string(hasVt)     + "\n" +
      "\tfaces_1: "     + std::to_string(faces_1)   + "\n" +
      "\tfaces_2: "     + std::to_string(faces_2)   + "\n" +
      "\tfaces_3: "     + std::to_string(faces_3)   + "\n" +
      "\tfaces_4: "     + std::to_string(faces_4)   + "\n";
    return message;
  }

  glm::vec1 Wavefront_Parser::split_1f(std::string &line)
  {
    std::istringstream iss(line);
    std::vector<float> temp;
    do
    {
      std::string subs;
      iss >> subs;
      temp.push_back(::atof(subs.c_str()));
    }
    while (iss);
  
    return glm::vec1(temp.at(1));
  }

  glm::vec2 Wavefront_Parser::split_2f(std::string &line)
  {
    std::istringstream iss(line);
    std::vector<float> temp;
    do
    {
      std::string subs;
      iss >> subs;
      temp.push_back(::atof(subs.c_str()));
    }
    while (iss);
    
    return glm::vec2(temp.at(1), temp.at(2));
  }

  glm::vec3 Wavefront_Parser::split_3f(std::string &line)
  {
    std::istringstream iss(line);
    std::vector<float> temp;
    do
    {
        std::string subs;
        iss >> subs;
        temp.push_back(::atof(subs.c_str()));
    }
    while (iss);
    
    return glm::vec3(temp.at(1), temp.at(2), temp.at(3));
  }

  std::vector<std::string> Wavefront_Parser::split_face(std::string &line)
  {
    std::istringstream buf(line);
  
    std::istream_iterator<std::string> beg(buf), end;
    std::vector<std::string> tokens(beg, end);

    return tokens;
  }

  void Wavefront_Parser::parse_faces(std::string &line, Wavefront_Description description)
  {        
    std::regex reg("([0-9]+)");
    std::smatch s_matches;
    std::vector<unsigned int> matches;
    
    // find any number in line, convert to int and add to vector matches
    while (std::regex_search(line, s_matches, reg))
    {
      matches.push_back(std::stoi(s_matches.str(1)));
      line = s_matches.suffix().str();
    }
    
    // parse line of format "f v v v"
    if (description == 1)
    {
      for (unsigned int &it : matches)
        temp_f_V.push_back(it);
    } 
    // parse line of format "f v/vt v/vt v/vt"
    else if (description == 2)
    {
      temp_f_V.push_back(matches.at(0));
      temp_f_V.push_back(matches.at(2));
      temp_f_V.push_back(matches.at(4));  

      temp_f_Vt.push_back(matches.at(1));
      temp_f_Vt.push_back(matches.at(3));
      temp_f_Vt.push_back(matches.at(5));
    } 
    // parse line of format "f v//vn v//vn v//vn"
    else if (description == 3)
    {
      temp_f_V.push_back(matches.at(0));
      temp_f_V.push_back(matches.at(2));
      temp_f_V.push_back(matches.at(4));  

      temp_f_Vn.push_back(matches.at(1));
      temp_f_Vn.push_back(matches.at(3));
      temp_f_Vn.push_back(matches.at(5));
    } 
    // parse line of format "f v/vt/vn v/vt/vn v/vt/vn"
    else if (description == 4)
    {
      temp_f_V.push_back(matches.at(0));
      temp_f_V.push_back(matches.at(3));
      temp_f_V.push_back(matches.at(6));

      temp_f_Vt.push_back(matches.at(1));
      temp_f_Vt.push_back(matches.at(4));
      temp_f_Vt.push_back(matches.at(7));

      temp_f_Vn.push_back(matches.at(2));
      temp_f_Vn.push_back(matches.at(5));
      temp_f_Vn.push_back(matches.at(8));
    }
  }
}