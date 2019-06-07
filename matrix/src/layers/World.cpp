#include "matrix/src/layers/World.h"
#ifdef MX_IMGUI_ACTIVE
  #include "matrix/src/platform/gui/GUI_ImGui_Flags.h"
#endif

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

namespace MX
{
  void check_folder_for_shaders();
  void check_folder_for_models();

  World &World::get()
  {
    static World instance;
    return instance;
  }

  World::~World()
  {
    for (auto *it : m_ExistingScenes)
    {
      MX_INFO_LOG("MX: World: Deleting Scene: " + it->m_Name);
      delete it;
      it = nullptr;
    }

    for (auto *it : m_Models)
    {
      MX_INFO_LOG("MX: World: Deleting Model: " + it->getName());
      delete it;
      it = nullptr;
    }

    for (auto *it : m_Shaders)
    {
      MX_INFO_LOG("MX: World: Deleting Shader: " + it->getName());
      delete it;
      it = nullptr;
    }

    m_ExistingScenes.clear();
    m_Models.clear();
    m_Shaders.clear();
  }

  void World::initialize()
  {
    // push trivial shader first so that it is the default one
    MX_SHADER *temp_shader = new MX_SHADER("trivial");
    m_Shaders.push_back(temp_shader);

    check_folder_for_shaders();
    check_folder_for_models();

    // initialize default scenes if there are any in EntryPoint.cpp
    for (auto *it : m_ExistingScenes)
      it->initialize();

    // initialize all shaders
    for (auto *it : m_Shaders)
      it->initialize();

    
      
    /*
      you could also load all models first here    
     */
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

  // gets all model files in respective folder
  void check_folder_for_models()
  {
    boost::filesystem::path p(MX_MODEL_PATH);

    std::vector<boost::filesystem::directory_entry> all_available_models_d;

    if (boost::filesystem::is_directory(p))
    {
      std::copy(boost::filesystem::directory_iterator(p), boost::filesystem::directory_iterator(), std::back_inserter(all_available_models_d));

      for (std::vector<boost::filesystem::directory_entry>::const_iterator it = all_available_models_d.begin(); it != all_available_models_d.end(); ++it)
      {
        std::string temp = (*it).path().string();
      #ifdef MX_PLATFORM_WINDOWS_X64
        std::size_t found_slash = temp.find_last_of("\\");
      #elif MX_PLATFORM_UNIX_X64
        std::size_t found_slash = temp.find_last_of("/");
      #endif
        std::size_t found_point = temp.find_last_of(".");
        temp = temp.substr(found_slash + 1, found_point - found_slash - 1);
        
        char *file_name = new char[temp.size()  + 1];
        std::copy(temp.begin(), temp.end(), file_name);
        file_name[temp.size()] = '\0';

      #ifdef MX_IMGUI_ACTIVE
        all_available_models.push_back(file_name);
      #endif
      }
    }

  #ifdef MX_IMGUI_ACTIVE
    MX_INFO_LOG("MX: Model: " + std::to_string(all_available_models.size()) + " files found");
  #endif
  }

  // gets all shader files in respective folder
  void check_folder_for_shaders()
  {
    boost::filesystem::path p(MX_SHADER_PATH);

    std::vector<boost::filesystem::directory_entry> all_available_shaders_d;

    if (boost::filesystem::is_directory(p))
    {
      std::copy(boost::filesystem::directory_iterator(p), boost::filesystem::directory_iterator(), std::back_inserter(all_available_shaders_d));

      for (std::vector<boost::filesystem::directory_entry>::const_iterator it = all_available_shaders_d.begin(); it != all_available_shaders_d.end(); ++it)
      {
        std::string temp = (*it).path().string();
      #ifdef MX_PLATFORM_WINDOWS_X64
        std::size_t found_slash = temp.find_last_of("\\");
      #elif MX_PLATFORM_UNIX_X64
        std::size_t found_slash = temp.find_last_of("/");
      #endif
        std::size_t found_point = temp.find_last_of(".");
        temp = temp.substr(found_slash + 1, found_point - found_slash - 1);
        
        char *file_name = new char[temp.size()  + 1];
        std::copy(temp.begin(), temp.end(), file_name);
        file_name[temp.size()] = '\0';

        bool shader_file_exists_already = 0;

        for (const auto *it : World::get().m_Shaders)
        {
          if (it->getName() == file_name)
            shader_file_exists_already = 1;
        }

        if (!shader_file_exists_already)
        {
          MX_SHADER *temp_shader = new MX_SHADER(file_name);
          World::get().m_Shaders.push_back(temp_shader);         
        }
      }
      
      MX_INFO_LOG("MX: Shader: " + std::to_string(World::get().m_Shaders.size()) + " files found");

    #ifdef MX_IMGUI_ACTIVE
      for (auto *it : World::get().m_Shaders)
        all_available_shaders.push_back(it->getName().c_str());
    #endif
    }    
  }
}