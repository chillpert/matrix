#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

#include <exception>
#include <string>

class mx_exception: public std::exception
{
public:
  explicit mx_exception(const char *message)
    : m_msg(message) { }

  explicit mx_exception(const std::string &message)
    : m_msg(message) { }

  virtual ~mx_exception() throw () {}

  virtual const char *what() const throw () { return m_msg.c_str(); }

protected:
  std::string m_msg;
};

class mx_entity_not_found : public mx_exception
{
public:
  explicit mx_entity_not_found(const char *message)
    : mx_exception(message) { }

  explicit mx_entity_not_found(const std::string &message)
    : mx_exception(message) { }

  virtual ~mx_entity_not_found() throw () { }

  virtual const char *what() const throw ()
  {
    std::string temp_msg = "MX: Exception: Entity not found: " + m_msg;
    return m_msg.c_str();
  }
};

class mx_invalid_type : public mx_exception
{
public:
  explicit mx_invalid_type(const char *message)
    : mx_exception(message) { }

  explicit mx_invalid_type(const std::string &message)
    : mx_exception(message) { }

  virtual ~mx_invalid_type() throw () { }

  virtual const char *what() const throw ()
  {
    std::string temp_msg = "MX: Exception: Invalid type: " + m_msg;
    return m_msg.c_str();
  }
};


#endif // CUSTOMEXCEPTION_H