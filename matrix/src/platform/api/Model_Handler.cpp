#include <Model_Handler.h>

namespace MX
{
  std::vector<std::string> existing_objects;

  void spawnObject(const std::string &object_name, const std::string &file_name)
  {
    bool object_exists = 0;
    
    for (const auto &it : existing_objects)
    {
      if (it == "file_name")
      {
        object_exists = 1;
      }
    }

    if (object_exists)
    {
      MX_INFO("MX: Model Handler: Object already exists: Continue without parsing");
    }
    else
    {
      MX_INFO("MX: Model Handler: Object does not exist: Continue with parsing");
      existing_objects.push_back(file_name);
      MX_MODEL temp(file_name);
    }
  }
}