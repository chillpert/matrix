#include "matrix/src/platform/api/Model_OpenGL.h"
#include "matrix/src/platform/api/Parser_Wavefront.h"

namespace MX
{
  Model_OpenGL::Model_OpenGL(const Model_OpenGL &model)
  {
    m_Name = model.m_Name;
    m_Path = model.m_Path;

    m_MaterialList = model.m_MaterialList;
    m_V = model.m_V;
    m_Vt = model.m_Vt;
    m_Vn = model.m_Vn;
    
    m_ModelObject = GL_ModelObjects(model.m_ModelObject);
  }
  
  Model_OpenGL::Model_OpenGL(const std::string &name, bool instantInitialize)
  {
    m_Name = name;
    m_Path = MX_MODEL_PATH + name;
    
    if (instantInitialize)
      initialize();
  }

  void Model_OpenGL::setName(const std::string &name)
  {
    m_Name = name;
    m_Path = MX_MODEL_PATH + name;
  }

  void Model_OpenGL::initialize()
  {
    if (m_Name.find(".obj"))
    {
      Wavefront_Parser parser(*this);
      parser.start();
      setGeometry(GL_TRIANGLES);
    }
    else
    {
      MX_FATAL("MX: Model: File format not supported");
    }
  }

  void Model_OpenGL::setGeometry(unsigned int draw_mode)
  {
    glGenVertexArrays(1, &m_ModelObject.VAO);
    glBindVertexArray(m_ModelObject.VAO);        
  
    if (1)
    {
      glGenBuffers(1, &m_ModelObject.VBO);
	    glBindBuffer(GL_ARRAY_BUFFER, m_ModelObject.VBO);
      glBufferData(GL_ARRAY_BUFFER, m_V.size() * sizeof(glm::vec3), &m_V[0], GL_STATIC_DRAW);
      glGenBuffers(1, &m_ModelObject.TBO);
	    glBindBuffer(GL_ARRAY_BUFFER, m_ModelObject.TBO);
      glBufferData(GL_ARRAY_BUFFER, m_Vt.size() * sizeof(glm::vec2), &m_Vt[0], GL_STATIC_DRAW);
	    glGenBuffers(1, &m_ModelObject.NBO);
	    glBindBuffer(GL_ARRAY_BUFFER, m_ModelObject.NBO);
      glBufferData(GL_ARRAY_BUFFER, m_Vn.size() * sizeof(glm::vec3), &m_Vn[0], GL_STATIC_DRAW);
    }
    else
    {
      MX_FATAL("MX: Model: Geometry");
    }
    m_ModelObject.num_elements = m_V.size();
    m_ModelObject.draw_mode = draw_mode;  
      
  }

  void Model_OpenGL::draw()
  {
    glBindVertexArray(m_ModelObject.VAO);
    if (1)
    {
      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, m_ModelObject.VBO);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
      glEnableVertexAttribArray(1);
      glBindBuffer(GL_ARRAY_BUFFER, m_ModelObject.TBO);
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
      glEnableVertexAttribArray(2);
      glBindBuffer(GL_ARRAY_BUFFER, m_ModelObject.NBO);
      glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    } else
    {
      MX_FATAL("MX: Model: Draw");
    }
  
    m_ModelObject.num_elements = m_V.size();

    glBindVertexArray(m_ModelObject.VAO);
    glDrawArrays(m_ModelObject.draw_mode, 0, m_ModelObject.num_elements);

    if (1)
    {
      glDisableVertexAttribArray(1);
      glDisableVertexAttribArray(2);
      glDisableVertexAttribArray(3);
    }
    else
    {
      MX_FATAL("MX: Model: Draw (2)");
    }
  }
}