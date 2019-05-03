#include "matrix/src/platform/api/Shader_OpenGL.h"

namespace MX
{
  Shader_OpenGL::Shader_OpenGL(const std::string &name, bool instantInitialization)
  {
    m_Name = name;
    m_VsPath.append(name + ".vert");
    m_FsPath.append(name + ".frag");

    if (instantInitialization)
      initialize();
  }

  Shader_OpenGL::Shader_OpenGL(const Shader_OpenGL &shader)
  {
    m_ID = shader.m_ID;

    m_Name = shader.m_Name;
    m_VsPath = shader.m_VsPath;
    m_FsPath = shader.m_FsPath;
    m_VsSource = shader.m_VsSource;
    m_FsSource = shader.m_FsSource;
  }

  void Shader_OpenGL::use() const
  {
    glUseProgram(m_ID); 
  }

  void Shader_OpenGL::initialize()
  {
    m_ID = glCreateProgram();

    m_VsSource = parseFile(m_VsPath);
    m_FsSource = parseFile(m_FsPath);
    
	  unsigned int vs = compile(GL_VERTEX_SHADER, m_VsSource);
	  unsigned int fs = compile(GL_FRAGMENT_SHADER, m_FsSource);

	  glAttachShader(m_ID, vs);
	  glAttachShader(m_ID, fs);
	  glLinkProgram(m_ID);
	  glValidateProgram(m_ID);

    errorCheck(m_ID, GL_LINK_STATUS);
      
	  glDeleteShader(vs);
	  glDeleteShader(fs);

    MX_SUCCESS("MX: API: OpenGL: Shader: " + m_Name);
  }

  void Shader_OpenGL::setBool(const std::string &name, const bool &value) const
  {         
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value); 
  }

  void Shader_OpenGL::setInt(const std::string &name, const int &value) const
  { 
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value); 
  }

  void Shader_OpenGL::setFloat(const std::string &name, const float &value) const
  { 
    glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value); 
  }

  void Shader_OpenGL::setfVec2(const std::string &name, const glm::fvec2 &value) const
  { 
    glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]); 
  }

  void Shader_OpenGL::setfVec3(const std::string &name, const glm::fvec3 &value) const
  { 
    glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]); 
  }

  void Shader_OpenGL::setfVec4(const std::string &name, const glm::fvec4 &value) const
  { 
    glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]); 
  }

  void Shader_OpenGL::setfMat2(const std::string &name, const glm::fmat2 &mat) const
  {
    glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }

  void Shader_OpenGL::setfMat3(const std::string &name, const glm::fmat3 &mat) const
  {
    glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }

  void Shader_OpenGL::setfMat4(const std::string &name, const glm::fmat4 &mat) const
  {
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }

  void use(Shader_OpenGL &shader)
  {
    glUseProgram(shader.getID());
  }

  unsigned int compile(unsigned int type, const std::string& source)
  {
    unsigned int ID = glCreateShader(type);
	  const char* src = source.c_str();
	  glShaderSource(ID, 1, &src, nullptr);
	  glCompileShader(ID);
  
    errorCheck(ID, GL_COMPILE_STATUS);

	  return ID;
  }

  void errorCheck(const unsigned int &ID, int type)
  {
    int success;
    char infoLog[512];
	  glGetProgramiv(ID, type, &success);

    if (!success)
    {
      glGetProgramInfoLog(ID, 512, NULL, infoLog);
      MX_FATAL("MX: Shader: " + std::string(infoLog));
    }
  }

  Shader_OpenGL Shader_OpenGL::operator=(const Shader_OpenGL &shader)
  {
    Shader_OpenGL temp(shader);
    return temp;
  }
}