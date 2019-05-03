#include "matrix/src/layers/World.h"

namespace MX
{
  World &World::get()
  {
    static World instance;
    return instance;
  }

  void World::initialize()
  {
    m_ActiveLevel->initialize();
  }

  void World::update()
  {
    m_ActiveLevel->update();
  }

  void World::render()
  {
    m_ActiveLevel->render();
  }

  void World::push(Level *level)
  {
    m_ExistingLevels.push_back(level);
    MX_INFO("MX: World: Level: " + level->m_Name + ": Added");
  }

  void World::pop(const std::string &name)
  {
    for (unsigned int i = 0; i < m_ExistingLevels.size(); i++)
    {
      if (m_ExistingLevels.at(i)->m_Name == name)
      {
        delete m_ExistingLevels.at(i);
        try 
        {
          m_ExistingLevels.erase(m_ExistingLevels.begin() + i);
        }
        catch (std::exception e)
        {
          MX_FATAL(e.what());
        }

        MX_WARN("MX: World: Level " + m_ExistingLevels.at(i)->m_Name + ": Deleted");
      }
    }
  }
}