#include "Shader_OpenGL.h"
#include "World.h"
#include "Application.h"

namespace MX
{
  Shader_OpenGL::Shader_OpenGL(const std::string &path, bool instant_init)
    : Shader(path)
  {
    if (instant_init)
      initialize(); 
  }

  Shader_OpenGL::~Shader_OpenGL()
  {
    glDeleteShader(m_ID);
  }

  void Shader_OpenGL::use() const
  {
    glUseProgram(m_ID); 
  }

  void Shader_OpenGL::initialize()
  {
    MX_INFO_LOG("MX: API: OpenGL: Shader: Initialization: " + m_Name);
    m_ID = glCreateProgram();

    m_VsSource = parseFile(m_VsPath);
    m_FsSource = parseFile(m_FsPath);
    
	  GLuint vs = compile(GL_VERTEX_SHADER, m_VsSource);
	  GLuint fs = compile(GL_FRAGMENT_SHADER, m_FsSource);

	  glAttachShader(m_ID, vs);
	  glAttachShader(m_ID, fs);
	  glLinkProgram(m_ID);
	  glValidateProgram(m_ID);
    
    if (!errorCheck(GL_LINK_STATUS))
    {
      glDeleteProgram(m_ID);
      glDeleteShader(vs);
      glDeleteShader(fs);
      return;
    }

    glDetachShader(m_ID, vs);
    glDetachShader(m_ID, fs);

    m_initialized = 1;
    MX_SUCCESS_LOG("MX: API: OpenGL: Shader: " + m_Name);
  }

  void Shader_OpenGL::update()
  {
    
  }


  u_int32_t Shader_OpenGL::compile(u_int32_t type, const std::string& source)
  {
    u_int32_t ID = glCreateShader(type);
	  const char* src = source.c_str();
	  glShaderSource(ID, 1, &src, nullptr);
	  glCompileShader(ID);

    if (!errorCheck(GL_COMPILE_STATUS))
    {
      MX_FATAL_LOG("MX: Shader: OpenGL: Compiling Failed: Deleting Shader");
      return -1;
    }

	  return ID;
  }

  bool Shader_OpenGL::errorCheck(int type) const
  {
    GLint success = 1;
    std::vector<char> infoLog;
	  glGetProgramiv(m_ID, type, &success);

    if (!success)
    {
      GLint maxLength = 0;

      switch (type)
      {
        case GL_LINK_STATUS:
        {
          glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &maxLength);
          infoLog.resize(maxLength);
          glGetProgramInfoLog(m_ID, maxLength, &maxLength, infoLog.data());
          break;
        }
        case GL_COMPILE_STATUS:
        {
          glGetShaderiv(m_ID, GL_INFO_LOG_LENGTH, &maxLength);
          glGetShaderInfoLog(m_ID, maxLength, &maxLength, infoLog.data());
          break;
        }
        default:
        {
          MX_FATAL("MX: Shader: OpenGL: Unkown Error Occured");
          break;
        }
      }

      std::string errorMessage;

      for (auto it : infoLog)
        errorMessage += it;

      MX_FATAL("MX: Shader: OpenGL: Error: " + errorMessage);

      return 0;
    }

    return 1;
  }

  void Shader_OpenGL::setBool(const std::string &name, const bool &value) const
  {         
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int) value); 
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
}