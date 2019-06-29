#include <World.h>
#ifdef MX_IMGUI_ACTIVE
  #include <GUI_ImGui_Flags.h>
#endif

#include <Application.h>

#define MX_INSTANT_MODEL_INIT

#ifdef MX_PLATFORM_UNIX_X64
  #include <boost/filesystem.hpp>
  #include <boost/range/iterator_range.hpp>
#elif MX_PLATFORM_WINDOWS_X64
  #include <boost/filesystem.hpp>
  #include <boost/range/iterator_range.hpp>
#endif

namespace MX
{
  void set_resource_files(const std::string &path_to_folder, std::string recurs_path = "");

  World &World::get_default_world()
  {
    static World instance;
    return instance;
  }

  World::~World()
  {
    MX_INFO_LOG("MX: World: Destructor");
  }

  std::shared_ptr<Model> World::getModel(const std::string &name) const
  {
    try
    {
      for (auto it : m_Models)
      {
        if (it->m_name == name)
        {
          if (!it->m_initialized) it->initialize();
          return it;
        }
      }

      throw mx_entity_not_found(name);
    }
    catch (const mx_entity_not_found &e)
    {
      MX_FATAL(e.what());
    }
  }

  std::shared_ptr<Shader> World::getShader(const std::string &name) const
  {
    try
    {
      for (auto it : m_Shaders)
      {
        if (it->m_Name == name)
        {
          if (!it->m_initialized) it->initialize();
          return it;
        }
      }

      throw mx_entity_not_found(name);
    }
    catch (const mx_entity_not_found &e)
    {
      MX_FATAL(e.what());
    }
  }

  std::shared_ptr<Texture> World::getTexture(const std::string &name) const
  {
    try
    {
      for (auto it : m_Textures)
      {
        if (it->m_Name == name)
        {
          if (!it->m_initialized) it->initialize();
          return it;
        }
      }

      throw mx_entity_not_found(name);
    }
    catch (const mx_entity_not_found &e)
    {
      MX_FATAL(e.what());
    }
  }

  std::shared_ptr<TextureProfile> World::getTextureProfile(std::shared_ptr<Texture> diffuse, std::shared_ptr<Texture> normal, std::shared_ptr<Texture> bump, std::shared_ptr<Texture> height) const
  {
    std::shared_ptr<TextureProfile> profile(new TextureProfile());

    try
    {
      for (auto it : m_Textures)
      {
        if (it->m_type.find("texture_diffuse") != std::string::npos)
          profile->diffuse = it;
        else if (it->m_type.find("texture_specular") != std::string::npos)
          profile->specular = it;
        else if (it->m_type.find("texture_normal") != std::string::npos)
          profile->normal = it;
        else if (it->m_type.find("texture_bump") != std::string::npos)
          profile->bump = it;
        else if (it->m_type.find("texture_height") != std::string::npos)
          profile->height = it;
      }

      if (profile->diffuse == nullptr)
        throw mx_entity_not_found(diffuse->m_Name);
    }
    catch (const mx_entity_not_found &e)
    {
      MX_FATAL(e.what());
    }
  }

  void World::initialize()
  {
    set_resource_files(MX_SHADER_PATH);
    set_resource_files(MX_MODEL_PATH);
    set_resource_files(MX_TEXTURE_PATH);

    for (auto it : m_ExistingScenes)
      it->initialize();
  }

  void World::update()
  {
    m_ActiveScene->update();
  }

  void World::render()
  {
    m_ActiveScene->render();
  }

  void World::push(std::shared_ptr<Scene> scene)
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
        m_ExistingScenes.at(i) = nullptr;
        m_ExistingScenes.erase(m_ExistingScenes.begin() + i);

        MX_WARN("MX: World: Scene " + m_ExistingScenes.at(i)->m_Name + ": Deleted");
      }
    }
  }

  void set_resource_files(const std::string &path_to_folder, std::string recurs_path)
  {
    bool model = 0;
    bool shader = 0;
    bool texture = 0;

    if (path_to_folder.find(MX_MODEL_PATH) != std::string::npos)
      model = 1;
    else if (path_to_folder.find(MX_SHADER_PATH) != std::string::npos)
      shader = 1;
    else if (path_to_folder.find(MX_TEXTURE_PATH) != std::string::npos)
      texture = 1;
    else
    {
      MX_FATAL("MX: Utils: Check folder for files: Path " + path_to_folder + " is not valid");
      return;
    }

    boost::filesystem::path p(path_to_folder);

    if (boost::filesystem::is_directory(p))
    {
      boost::filesystem::directory_iterator end_itr;

      for (boost::filesystem::directory_iterator itr(p); itr != end_itr; ++itr)
      {
        if (boost::filesystem::is_directory(itr->path()))
        {
          std::string temp_path = itr->path().string();
          recurs_path = temp_path.substr(temp_path.find_last_of('/') + 1);
          set_resource_files(temp_path, recurs_path + '/');
          recurs_path = "";
        }
        else
        {
          std::string temp = itr->path().string();
        #ifdef MX_PLATFORM_WINDOWS_X64
          std::size_t found_slash = temp.find_last_of("\\");
        #elif MX_PLATFORM_UNIX_X64
          std::size_t found_slash = temp.find_last_of("/");
        #endif
          std::size_t found_point = temp.find_last_of(".");

          std::string temp_without_ending = recurs_path + temp.substr(found_slash + 1, found_point - found_slash - 1);
          std::string temp_with_ending = recurs_path + temp.substr(found_slash + 1);

          char *file_name = new char[temp_without_ending.size() + 1];
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
          
            for (const auto it : MX_WORLD.m_Models)
            {
              if (it->m_name == file_name)
                model_file_exists_already = 1;
            }

            if (!model_file_exists_already && std::string(file_name_with_ending).find(".obj") != std::string::npos)
            {
              std::shared_ptr<Model> temp_model(new Model(file_name_with_ending));
              MX_WORLD.m_Models.push_back(temp_model);

            #ifdef MX_IMGUI_ACTIVE
              model_test.push_back({{static_cast<int>(MX_WORLD.m_Models.size()), temp_model}});
              all_models.push_back(file_name);
            #endif
            }
          }

        /*#####################
                SHADER
        #####################*/
          else if (shader)
          {
            bool shader_file_exists_already = 0;

            for (const auto it : MX_WORLD.m_Shaders)
            {
              if (it->m_Name == file_name)
                shader_file_exists_already = 1;
            }

            if (!shader_file_exists_already)
            {
              std::shared_ptr<Shader> temp_shader(new MX_SHADER(file_name));
              MX_WORLD.m_Shaders.push_back(temp_shader);
            #ifdef MX_IMGUI_ACTIVE
              all_shaders.push_back(file_name); 
            #endif
            }
          }

        /*#####################
              TEXTURES
        #####################*/
          else if (texture)
          {
            bool texture_file_exists_already = 0;

            for (auto it : MX_WORLD.m_Textures)
            {
              if (it->m_Name == file_name && (std::string(file_name).find(".jpg") != std::string::npos || std::string(file_name).find(".png") != std::string::npos))
                texture_file_exists_already = 1;
            }

            if (!texture_file_exists_already)
            {
              std::shared_ptr<MX_TEXTURE> temp_texture(new MX_TEXTURE(file_name_with_ending));
              MX_WORLD.m_Textures.push_back(temp_texture);
            #ifdef MX_IMGUI_ACTIVE
              all_diffuse_maps.push_back(file_name);
            #endif
            }
          }
        }
      }

      if (model)
        MX_INFO_LOG("MX: Model: " + std::to_string(MX_WORLD.m_Models.size()) + " files found");
      else if (shader)
        MX_INFO_LOG("MX: Shader: " + std::to_string(MX_WORLD.m_Shaders.size()) + " files found");
      else if (texture)
        MX_INFO_LOG("MX: Texture: " + std::to_string(MX_WORLD.m_Textures.size()) + " files found");
		}
  	else
  	{
  	  MX_FATAL("MX: Utils: Check folder for files: Path " + path_to_folder + " is not valid");
      return;
  	}
  }
}