#include "matrix/src/layers/World.h"
#ifdef MX_IMGUI_ACTIVE
  #include "matrix/src/platform/gui/GUI_ImGui_Flags.h"
#endif

#ifdef MX_PLATFORM_UNIX_X64
  #include <boost/filesystem.hpp>
  #include <boost/range/iterator_range.hpp>
#elif MX_PLATFORM_WINDOWS_X64
  // files are stored in externals for better portabilitys
  #include <BOOST/filesystem.hpp>
  #include <BOOST/range/iterator_range.hpp>
#endif

namespace MX
{
  void set_resource_files(const std::string &path_to_folder);

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

    for (auto *it : m_Textures)
    {
      MX_INFO_LOG("MX: World: Deleting Texture: " + it->getName());
      delete it;
      it = nullptr;
    }

    m_ExistingScenes.clear();
    m_Models.clear();
    m_Shaders.clear();
  }

  MX_MODEL *World::getModel(const std::string &name, bool instant_init)
  {
    for (auto *it : m_Models)
    {
      if (it->getName() == name)
      {
        if (instant_init)
          it->initialize();
        return it;
      }
    }

    throw std::exception();
  }

  MX_SHADER *World::getShader(const std::string &name, bool instant_init)
  {
    for (auto *it : m_Shaders)
    {
      if (it->getName() == name)
      {
        if (instant_init)
          it->initialize();
        return it;
      }
    }

    throw std::exception();
  }

  MX_TEXTURE *World::getTexture(const std::string &name, bool instant_init)
  {
    for (auto *it : m_Textures)
    {
      if (it->getName() == name)
      {
        if (instant_init)
          it->initialize();
        return it;
      }
    }

    throw std::exception();
  }

  void World::initialize()
  {
    // push trivial shader first so that it is the default one
    //MX_SHADER *temp_shader = new MX_SHADER("blinn_phong");
    //m_Shaders.push_back(temp_shader);

  #ifdef MX_IMGUI_ACTIVE
    //all_available_shaders.push_back("blinn_phong");
  #endif

    set_resource_files(MX_SHADER_PATH);
    set_resource_files(MX_MODEL_PATH);
    set_resource_files(MX_TEXTURE_PATH);

  #ifdef MX_INSTANT_SCENE_INIT
    for (auto *it : m_ExistingScenes)
      it->initialize();
  #endif

  #ifdef MX_INSTANT_SHADER_INIT
    for (auto *it : m_Shaders)
      it->initialize();
  #endif

  #ifdef MX_INSTANT_TEXTURE_INIT
    for (auto *it : m_Textures)
      it->initialize();
  #endif

  #ifdef MX_INSTANT_MODEL_INIT
    for (auto *it : m_Models)
      it->initialize();
  #endif
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

  void set_resource_files(const std::string &path_to_folder)
  {
    bool model = 0;
    bool shader = 0;
    bool texture = 0;

    if (path_to_folder == MX_MODEL_PATH)
      model = 1;
    else if (path_to_folder == MX_SHADER_PATH)
      shader = 1;
    else if (path_to_folder == MX_TEXTURE_PATH)
      texture = 1;
    else
    {
      MX_FATAL("MX: Utils: Check folder for files: Path " + path_to_folder + " is not valid");
      return;
    }

    boost::filesystem::path p(path_to_folder);

    std::vector<boost::filesystem::directory_entry> all_available_files_d;

    if (boost::filesystem::is_directory(p))
    {
      std::copy(boost::filesystem::directory_iterator(p), boost::filesystem::directory_iterator(), std::back_inserter(all_available_files_d));

      for (std::vector<boost::filesystem::directory_entry>::const_iterator it = all_available_files_d.begin(); it != all_available_files_d.end(); ++it)
      {
        std::string temp = (*it).path().string();
			#ifdef MX_PLATFORM_WINDOWS_X64
        std::size_t found_slash = temp.find_last_of("\\");
      #elif MX_PLATFORM_UNIX_X64
        std::size_t found_slash = temp.find_last_of("/");
      #endif
        std::size_t found_point = temp.find_last_of(".");

        std::string temp_without_ending = temp.substr(found_slash + 1, found_point - found_slash - 1);
        std::string temp_with_ending = temp.substr(found_slash + 1);

        char *file_name = new char[temp_without_ending.size()  + 1];
        std::copy(temp_without_ending.begin(), temp_without_ending.end(), file_name);
        file_name[temp_without_ending.size()] = '\0';

				char *file_name_with_ending = new char[temp_with_ending.size()  + 1];
        std::copy(temp_with_ending.begin(), temp_with_ending.end(), file_name_with_ending);
        file_name_with_ending[temp_with_ending.size()] = '\0';

			/*#####################
							MODELS
			#####################*/
      	if (model)
      	{
      	  bool model_file_exists_already = 0;
				
      	  for (const auto *it : World::get().m_Models)
      	  {
      	    if (it->getName() == file_name)
      	      model_file_exists_already = 1;
      	  }

      	  if (!model_file_exists_already)
      	  {
          #ifdef MX_INSTANT_MODEL_INIT
      	    MX_MODEL *temp_model = new MX_MODEL(file_name_with_ending);
      	    World::get().m_Models.push_back(temp_model);
					#endif

          #ifdef MX_IMGUI_ACTIVE
						all_available_models.push_back(file_name);
					#endif 
      	  }
      	}

			/*#####################
							SHADER
			#####################*/
      	else if (shader)
      	{
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
					#ifdef MX_IMGUI_ACTIVE
      	    all_available_shaders.push_back(file_name); 
      		#endif
					}
      	}

			/*#####################
						TEXTURES
			#####################*/
      	else if (texture)
      	{
      	  bool texture_file_exists_already = 0;

      	  for (const auto *it : World::get().m_Textures)
      	  {
      	    if (it->getName() == file_name)
      	      texture_file_exists_already = 1;
      	  }

      	  if (!texture_file_exists_already)
      	  {
      	    MX_TEXTURE *temp_texture = new MX_TEXTURE(file_name_with_ending);
      	    World::get().m_Textures.push_back(temp_texture);
					#ifdef MX_IMGUI_ACTIVE
      	    all_available_textures.push_back(file_name);
      		#endif
					}	
      	}
			}
      
			if (model)
   			MX_INFO_LOG("MX: Model: " + std::to_string(World::get().m_Models.size()) + " files found");
			else if (shader)
				MX_INFO_LOG("MX: Shader: " + std::to_string(World::get().m_Shaders.size()) + " files found");
			else if (texture)
				MX_INFO_LOG("MX: Texture: " + std::to_string(World::get().m_Textures.size()) + " files found");
		}
  	else
  	{
  	  MX_FATAL("MX: Utils: Check folder for files: Path " + path_to_folder + " is not valid");
      return;
  	}
  }
}