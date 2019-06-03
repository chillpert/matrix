#include "matrix/src/layers/World.h"

namespace MX
{
  World &World::get()
  {
    static World instance;
    return instance;
  }

  World::~World()
  {
    for (Scene *it : m_ExistingScenes)
    {
      MX_INFO_LOG("World: Deleted Scene: " + it->m_Name);
      delete it;
      it = nullptr;
    }

    m_ExistingScenes.clear();
  }

  void World::initialize()
  {
    //for (auto &it : m_ExistingScenes)
    //  it->initialize();

    MX_SHADER temp("trivial");
    m_Shaders.push_back(temp);
  }

  void World::update()
  {
    m_ActiveScene->update();
  }

  void World::render()
  {
    m_ActiveScene->render();
  }

  void World::push(Scene *scene)
  {
    m_ExistingScenes.push_back(scene);
    m_ActiveScene = scene;
    scene->initialize();
    MX_INFO("MX: World: Scene: " + scene->m_Name + ": Added");
  }

  void World::pop(const std::string &name)
  {
    for (unsigned int i = 0; i < m_ExistingScenes.size(); i++)
    {
      if (m_ExistingScenes.at(i)->m_Name == name)
      {
        delete m_ExistingScenes.at(i);
        m_ExistingScenes.at(i) = nullptr;
        try 
        {
          m_ExistingScenes.erase(m_ExistingScenes.begin() + i);
        }
        catch (std::exception e)
        {
          MX_FATAL(e.what());
        }

        MX_WARN("MX: World: Scene " + m_ExistingScenes.at(i)->m_Name + ": Deleted");
      }
    }
  }
}