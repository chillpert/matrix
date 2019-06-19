#ifndef MODEL_HANDLER_H
#define MODEL_HANDLER_H

#include <stdafx.h>
#include <Model.h>
#include <Model_OpenGL.h>

// use this macro to spawn in objects
#define MX_SPAWN_OBJECT(object_name, file_name) MX::spawnObject(object_name, file_name);

namespace MX
{
  // keep track of already parsed object files
  extern std::vector<std::string> existing_objects;

  MX_API void spawnObject(const std::string &object_name, const std::string &file_name);
}

#endif // MODEL_HANDLER_H