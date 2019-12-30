#include "World.h"
#ifdef MX_IMGUI_ACTIVE
  #include "GUI_ImGui_Flags.h"
#endif

#include "Application.h"

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
  void log_resource_files();

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

    return nullptr;
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

    return nullptr;
  }

  std::shared_ptr<Texture> World::getTexture(const std::string &name) const
  {
    try
    {
      for (auto it : m_diffuse_maps)
      {
        if (it->m_Name == name)
        {
          if (!it->m_initialized) it->initialize();
          return it;
        }
      }

      for (auto it : m_specular_maps)
      {
        if (it->m_Name == name)
        {
          if (!it->m_initialized) it->initialize();
          return it;
        }
      }

      for (auto it : m_normal_maps)
      {
        if (it->m_Name == name)
        {
          if (!it->m_initialized) it->initialize();
          return it;
        }
      }

      for (auto it : m_bump_maps)
      {
        if (it->m_Name == name)
        {
          if (!it->m_initialized) it->initialize();
          return it;
        }
      }

      for (auto it : m_height_maps)
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

    return nullptr;
  }

  void World::initialize()
  {
    set_resource_files(MX_SHADER_PATH);
    set_resource_files(MX_MODEL_PATH);
    set_resource_files(MX_TEXTURE_PATH);
    log_resource_files();

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

  static int model_counter = 0;
  static int shader_counter = 0;
  static int diffuse_tex_counter = 0;
  static int specular_tex_counter = 0;
  static int normal_tex_counter = 0;
  static int bump_tex_counter = 0;
  static int height_tex_counter = 0;

  void log_resource_files()
  {
    MX_INFO_LOG("MX: Model: " + std::to_string(model_counter) + " files found");

    MX_INFO_LOG("MX: Shader: " + std::to_string(shader_counter) + " files found");

    MX_INFO_LOG("MX: Diffuse Maps:  " + std::to_string(diffuse_tex_counter) + " files found");
    MX_INFO_LOG("MX: Specular Maps: " + std::to_string(specular_tex_counter) + " files found");
    MX_INFO_LOG("MX: Normal Maps:   " + std::to_string(normal_tex_counter) + " files found");
    MX_INFO_LOG("MX: Bump Maps:     " + std::to_string(bump_tex_counter) + " files found");
    MX_INFO_LOG("MX: Height Maps:   " + std::to_string(height_tex_counter) + " files found");
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
        std::string temp_path = itr->path().string();
        
      #ifdef MX_PLATFORM_WINDOWS_X64
        auto found = temp_path.find_last_of('\\');
        temp_path.at(found) = '/';
      #endif

        if (boost::filesystem::is_directory(itr->path()))
        {
        #ifdef MX_PLATFORM_UNIX_X64 
          recurs_path = temp_path.substr(temp_path.find_last_of('/') + 1);
          set_resource_files(temp_path, recurs_path + '/');
          
        #elif MX_PLATFORM_WINDOWS_X64
          recurs_path = temp_path.substr(temp_path.find_last_of('/') + 1);
          set_resource_files(temp_path, recurs_path + '/');
        #endif
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
              ++model_counter;
              std::shared_ptr<Model> temp_model = std::make_shared<Model>(file_name_with_ending);
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
              ++shader_counter;
              std::shared_ptr<Shader> temp_shader = std::make_shared<MX_SHADER>(file_name);
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

            for (auto it : MX_WORLD.m_diffuse_maps)
            {
              if (it->m_Name == file_name && (std::string(file_name).find(".jpg") != std::string::npos || std::string(file_name).find(".png") != std::string::npos))
                texture_file_exists_already = 1;
            }

            for (auto it : MX_WORLD.m_normal_maps)
            {
              if (it->m_Name == file_name && (std::string(file_name).find(".jpg") != std::string::npos || std::string(file_name).find(".png") != std::string::npos))
                texture_file_exists_already = 1;
            }

            for (auto it : MX_WORLD.m_specular_maps)
            {
              if (it->m_Name == file_name && (std::string(file_name).find(".jpg") != std::string::npos || std::string(file_name).find(".png") != std::string::npos))
                texture_file_exists_already = 1;
            }

            for (auto it : MX_WORLD.m_bump_maps)
            {
              if (it->m_Name == file_name && (std::string(file_name).find(".jpg") != std::string::npos || std::string(file_name).find(".png") != std::string::npos))
                texture_file_exists_already = 1;
            }

            for (auto it : MX_WORLD.m_height_maps)
            {
              if (it->m_Name == file_name && (std::string(file_name).find(".jpg") != std::string::npos || std::string(file_name).find(".png") != std::string::npos))
                texture_file_exists_already = 1;
            }

            if (!texture_file_exists_already)
            {
              std::shared_ptr<MX_TEXTURE> temp_texture = std::make_shared<MX_TEXTURE>(file_name_with_ending);

              if (itr->path().string().find("diffuse") != std::string::npos)
              {
                ++diffuse_tex_counter;
                temp_texture->m_type = "texture_diffuse";
                all_diffuse_maps.push_back(file_name);
                MX_WORLD.m_diffuse_maps.push_back(temp_texture);
              }
              else if (itr->path().string().find("normal") != std::string::npos)
              {
                ++normal_tex_counter;
                temp_texture->m_type = "texture_normal";
                all_normal_maps.push_back(file_name);
                MX_WORLD.m_normal_maps.push_back(temp_texture);
              }
              else if (itr->path().string().find("specular") != std::string::npos)
              {
                ++specular_tex_counter;
                temp_texture->m_type = "texture_specular";
                all_specular_maps.push_back(file_name);
                MX_WORLD.m_specular_maps.push_back(temp_texture);
              }
              else if (itr->path().string().find("bump") != std::string::npos)
              {
                ++bump_tex_counter;
                temp_texture->m_type = "texture_bump";
                all_bump_maps.push_back(file_name);
                MX_WORLD.m_bump_maps.push_back(temp_texture);
              }
              else if (itr->path().string().find("height") != std::string::npos)
              {
                ++height_tex_counter;
                temp_texture->m_type = "texture_height";
                all_height_maps.push_back(file_name);
                MX_WORLD.m_height_maps.push_back(temp_texture);
              }
            }
          }
        }
      }
    }
    else
    {
      MX_FATAL("MX: Utils: Check folder for files: Path " + path_to_folder + " is not valid");
      return;
    }
  }

  glm::vec3 parse_vec3(std::string str)
  {
    glm::vec3 res(0.0f);

    // remove vec3( - part
    str = str.substr(str.find("(") + 1);

    // find first comma
    auto first_comma = str.find_first_of(",");
    // set first number
    res.x = stof(str.substr(0, first_comma));
    // remove first number
    str = str.substr(first_comma + 1);

    // find second comma
    auto second_comma = str.find_first_of(",");
    // set second number
    res.y = stof(str.substr(0, second_comma));
    // remove second number
    str = str.substr(second_comma + 1);

    // find last bracket
    auto last_bracket = str.find_first_of(")");
    // set third number
    res.z = stof(str.substr(0, last_bracket));

    return res;
  }

  std::string parse_single_string(const std::string& str, bool find_first_of = false)
  {
    if (find_first_of)
      return str.substr(str.find_first_of("{") + 1, str.find_first_of("}") - str.find_first_of("{") - 1);
    else
      return str.substr(str.find_first_of("{") + 1, str.find_last_of("}") - str.find_first_of("{") - 1);
  }

  std::shared_ptr<Node> find_node_in_vec(std::vector<std::shared_ptr<Node>> nodes, const std::string& name)
  {
    for (std::shared_ptr<Node> it : nodes)
    {
      if (it->m_Name == name)
        return it;
    }

    return nullptr;
  }
  
  bool World::load_scene(const std::string &name)
  {
    // load scene for the first time
    std::ifstream file;
    file.open(MX_SCENES_PATH + name);

    // name, name of parent, names of children, node type
    std::vector<std::tuple<std::string, std::string, std::vector<std::string>, NodeType>> nodes_config;
    std::tuple<std::string, std::string, std::vector<std::string>, NodeType> tp;
    std::string line = "";

    bool parsing_scene = false;
    bool parsing_camera = false;
    bool parsing_node = false;

    std::shared_ptr<Scene> scene = std::make_shared<Scene>("__UNDEF__");
    
    if (file.is_open())
    {
      /*
        First Pass:
          - creates nodes (according to type)
          - stores names of parent and children of each node
          - parse scene name
          - parse camera
      */
      while (std::getline(file, line))
      {
        std::string line_temp = line;
        if (line == "Scene")
        {
          parsing_scene = true;
          parsing_camera = false;
          parsing_node = false;
          continue;  
        }
      
        if (line == "Camera")
        {
          parsing_camera = true;
          parsing_scene = false;
          parsing_node = false;
          continue;
        }

        if (line == "Node")
        {
          parsing_node = true;
          parsing_camera = false;
          parsing_scene = false;
          continue;
        }

        if (parsing_scene)
        {
          auto tag = line.find("@Name");

          if (tag != std::string::npos)
          {
            scene->m_Name = parse_single_string(line);
          }
          else
            parsing_scene = false;

          // if already loaded once then just use pointer to scene
          bool already_exists = false;
          std::shared_ptr<Scene> new_scene = nullptr;
          for (const std::shared_ptr<Scene> it : m_ExistingScenes)
          {
            if (it->m_Name == name)
            {
              already_exists = true;
              new_scene = it;
            }
          }

          if (already_exists)
          {
            MX_INFO("MX: World: Load Scene: Scene " + name + " has already been loaded. Using existing data");
            m_ActiveScene = new_scene;
            return true;
          }
        }
        else if (parsing_camera)
        {
          auto tag_position = line_temp.find("@Position");
          auto tag_front = line_temp.find("@Front");

          if (tag_position != std::string::npos)
          {
            auto bracket_l = line_temp.find("{");  
            scene->m_Cam.m_Position = parse_vec3(line_temp.substr(bracket_l + 1, line_temp.length() - bracket_l - 2));
          }
          else if (tag_front != std::string::npos)
          {
            auto bracket_l = line_temp.find("{");  
            scene->m_Cam.m_Front = parse_vec3(line_temp.substr(bracket_l + 1, line_temp.length() - bracket_l - 2));
          }
          else
            parsing_camera = false;
        }
        else if (parsing_node)
        {
          auto tag_name = line.find("@Name");
          auto tag_children = line.find("@Children");
          auto tag_parent = line.find("@Parent");
          auto tag_type = line.find("@Type");

          if (tag_name != std::string::npos)
          {
            std::get<0>(tp) = parse_single_string(line_temp);
          }
          else if (tag_children != std::string::npos)
          {
            std::string temp = parse_single_string(line_temp);
            
            size_t amount = std::count(temp.begin(), temp.end(), '{');
            for (size_t i = 0; i < amount; ++i)
            {
              std::string str = parse_single_string(temp, true);
              size_t difference = str.length() + 2; // +2 because of { and }
              temp = temp.substr(difference);
              std::get<2>(tp).push_back(str);
            }
          }
          else if (tag_parent != std::string::npos)
          {
            std::get<1>(tp) = parse_single_string(line_temp);
          }
          else if (tag_type != std::string::npos)
          {
            std::string temp = parse_single_string(line_temp);
            if (temp == "type_node")
              std::get<3>(tp) = NodeType::type_node;
            else if (temp == "type_geometry")
              std::get<3>(tp) = NodeType::type_geometry;
            else if (temp == "type_container")
              std::get<3>(tp) = NodeType::type_container;
            else if (temp == "type_light")
              std::get<3>(tp) = NodeType::type_light;
            else if (temp == "type_directionalLight")
              std::get<3>(tp) = NodeType::type_directionalLight;
            else if (temp == "type_spotLight")
              std::get<3>(tp) = NodeType::type_spotLight;
            else if (temp == "type_pointLight")
              std::get<3>(tp) = NodeType::type_pointLight;      
          }
          else
          {
            parsing_node = false;

            // add to nodes_config
            nodes_config.push_back(tp);

            // reset tp once a node is finished parsing
            std::get<0>(tp) = "__UNDEF__";
            std::get<1>(tp) = "__UNDEF__";
            std::get<2>(tp).clear();
            std::get<3>(tp) = NodeType::type_node;
          }
        }
      }
    }
    else
    {
      MX_FATAL("MX: World: Load Scene: Can not open file");
      return false;
    }
    
    // store all nodes inside here
    std::vector<std::shared_ptr<Node>> nodes;
    
    // create nodes
    for (const auto& it : nodes_config)
    {
      switch (std::get<3>(it))
      {
        case NodeType::type_node:
        {
          MX_FATAL("MX: World: Load Scene: Creation of a node of the base class is not possible");
          break;
        }
        case NodeType::type_geometry:
        {
          nodes.push_back(std::make_shared<GeometryNode>(std::get<0>(it)));
          break;
        }
        case NodeType::type_container:
        {
          nodes.push_back(std::make_shared<ContainerNode>(std::get<0>(it)));
          break;
        }
        case NodeType::type_light:
        {
          MX_FATAL("MX: World: Load Scene: Creation of a node of the light node class is not possible");
          break;
        }
        case NodeType::type_directionalLight:
        {
          nodes.push_back(std::make_shared<DirectionalLightNode>(std::get<0>(it)));
          break;
        }
        case NodeType::type_spotLight:
        {
          nodes.push_back(std::make_shared<SpotLightNode>(std::get<0>(it)));
          break;
        }
        case NodeType::type_pointLight:
        {
          nodes.push_back(std::make_shared<PointLightNode>(std::get<0>(it)));
          break;
        }
        default:
        {
          MX_FATAL("MX: World: Load Scene: Unkown node type");
          break;
        }
      }
    }

    /*
      Second Pass:
        - sets members of nodes
    */

    std::shared_ptr<Node> node;

    // reset file
    file.clear();
    file.seekg(0, file.beg);

    parsing_node = false;

    if (file.is_open())
    {
      while (std::getline(file, line))
      {
        std::string line_temp = line;

        if (line == "Node")
        {
          parsing_node = true;
          continue;
        }
        
        if (parsing_node)
        {
          // node
          auto tag_name = line_temp.find("@Name");
          auto tag_shader = line_temp.find("@Shader");
          auto tag_transform = line_temp.find("@Transform");
          auto tag_visible = line_temp.find("@Visible");
          auto tag_children = line.find("@Children");
          auto tag_parent = line.find("@Parent");
          auto tag_type = line.find("@Type");

          // geometry node
          auto tag_model = line.find("@Model");
          auto tag_texture = line.find("@TextureProfile");
          auto tag_material = line.find("@MaterialProfile");

          // light node
          auto tag_ambient = line.find("@Ambient");
          auto tag_diffuse = line.find("@Diffuse");
          auto tag_specular = line.find("@Specular");
          auto tag_ambient_strength = line.find("@Strength");

          // directional light node
          auto tag_direction = line.find("@DirectionalDirection");
          
          // point light node
          auto tag_position = line.find("@PointPosition");
          auto tag_constant = line.find("@PointConstant");
          auto tag_linear = line.find("@PointLinear");
          auto tag_quadratic = line.find("@PointQuadratic");

          // spot light node
          auto tag_position_2 = line.find("@SpotPosition");
          auto tag_direction_2 = line.find("@SpotDirection");
          auto tag_constant_2 = line.find("@SpotConstant");
          auto tag_linear_2 = line.find("@SpotLinear");
          auto tag_quadratic_2 = line.find("@SpotQuadratic");
          auto tag_cut_off = line.find("@CutOff");
          auto tag_outer_cut_off = line.find("@OuterCutOff");

          if (tag_name != std::string::npos)
          {
            node = find_node_in_vec(nodes, parse_single_string(line_temp));
          }
          else if (tag_shader != std::string::npos)
          {
            node->setShader(getShader(parse_single_string(line_temp)));
          }
          else if (tag_transform != std::string::npos
          {
            std::string temp = parse_single_string(line_temp);

            for (int i = 0; i < 3; ++i)
            {
              std::string str = parse_single_string(temp, true);
              size_t difference = str.length() + 3; // +3 because of X, { and }
              temp = temp.substr(difference);

              if (i == 0)
                node->m_Trans.m_translation = parse_vec3(str);
              else if (i == 1)
                node->m_Trans.m_rotation = parse_vec3(str);
              else if (i == 2)
                node->m_Trans.m_scale = parse_vec3(str);
            }
          }
          else if (tag_visible != std::string::npos)
          {
            auto temp = parse_single_string(line_temp);
            if (temp == "1")
              node->m_visible = true;
            else
              node->m_visible = false;
          }
          // do nothing (this has already been taken care of in the first pass)
          else if (tag_type != std::string::npos) { }
          else if (tag_parent != std::string::npos) { }
          else if (tag_children != std::string::npos) { }
          else if (tag_model != std::string::npos)
          {
            auto geometry_node_ptr = dynamic_cast<GeometryNode*>(node.get());
            geometry_node_ptr->m_Model = getModel(parse_single_string(line_temp));
          }
          else if (tag_texture != std::string::npos)
          {
            TextureProfile textures;

            auto geometry_node_ptr = dynamic_cast<GeometryNode*>(node.get());
            
            std::string temp = parse_single_string(line_temp);
      
            size_t amount = std::count(temp.begin(), temp.end(), '{');
            for (int i = 0; i < amount; ++i)
            {            
              std::string temp_ = temp;
              std::string str = parse_single_string(temp, true);
              size_t difference = str.length() + 3; // +3 because of X, { and }
              temp = temp.substr(difference);

              if (temp_.find("D{"))
                textures.diffuse = getTexture(str);
              else if (temp_.find("S{"))
                textures.specular = getTexture(str);
              else if (temp_.find("N{"))
                textures.normal = getTexture(str);
              else if (temp_.find("B{"))
                textures.bump = getTexture(str);
              else if (temp_.find("H{"))
                textures.height = getTexture(str);
            }

            geometry_node_ptr->setTextureProfile(textures);
          } 
          else if (tag_material != std::string::npos)
          {
            auto geometry_node_ptr = dynamic_cast<GeometryNode*>(node.get());
            
            std::string temp = parse_single_string(line_temp);
            for (int i = 0; i < 4; ++i)
            {
              std::string temp_ = temp;
              std::string str = parse_single_string(temp, true);
              size_t difference = str.length() + 3;
              temp = temp.substr(difference);

              if (temp_.find("A{"))
                geometry_node_ptr->m_material.ambient = parse_vec3(str);
              else if (temp_.find("D{"))
                geometry_node_ptr->m_material.diffuse = parse_vec3(str);
              else if (temp_.find("S{"))
                geometry_node_ptr->m_material.specular = parse_vec3(str);
              else if (temp_.find("s{"))
                geometry_node_ptr->m_material.shininess = stof(str);
            }
          } 
          else if (tag_ambient != std::string::npos)
          {
            auto light_node_ptr = dynamic_cast<LightNode*>(node.get());
            light_node_ptr->ambient = parse_vec3(parse_single_string(line));
          } 
          else if (tag_diffuse != std::string::npos)
          {
            auto light_node_ptr = dynamic_cast<LightNode*>(node.get());
            light_node_ptr->diffuse = parse_vec3(parse_single_string(line));
          } 
          else if (tag_specular != std::string::npos)
          {
            auto light_node_ptr = dynamic_cast<LightNode*>(node.get());
            light_node_ptr->specular = parse_vec3(parse_single_string(line));
          } 
          else if (tag_ambient_strength != std::string::npos)
          {
            auto light_node_ptr = dynamic_cast<LightNode*>(node.get());
            light_node_ptr->ambient_strength = stof(parse_single_string(line));
          } 
          else if (tag_direction != std::string::npos)
          {
            auto directional_light_node_ptr = dynamic_cast<DirectionalLightNode*>(node.get());
            directional_light_node_ptr->direction = parse_vec3(parse_single_string(line));
          } 
          else if (tag_position != std::string::npos)
          {
            auto point_light_node_ptr = dynamic_cast<PointLightNode*>(node.get());
            point_light_node_ptr->position = parse_vec3(parse_single_string(line));
          } 
          else if (tag_constant != std::string::npos)
          {
            auto point_light_node_ptr = dynamic_cast<PointLightNode*>(node.get());
            point_light_node_ptr->constant = stof(parse_single_string(line));
          } 
          else if (tag_linear != std::string::npos)
          {
            auto point_light_node_ptr = dynamic_cast<PointLightNode*>(node.get());
            point_light_node_ptr->linear = stof(parse_single_string(line));
          }
          else if (tag_quadratic != std::string::npos)
          {
            auto point_light_node_ptr = dynamic_cast<PointLightNode*>(node.get());
            point_light_node_ptr->quadratic = stof(parse_single_string(line));
          }
          else if (tag_position_2 != std::string::npos)
          {
            auto spot_light_node_ptr = dynamic_cast<SpotLightNode*>(node.get());
            spot_light_node_ptr->position = parse_vec3(parse_single_string(line));
          }
          else if (tag_direction_2 != std::string::npos)
          {
            auto spot_light_node_ptr = dynamic_cast<SpotLightNode*>(node.get());
            spot_light_node_ptr->direction = parse_vec3(parse_single_string(line));
          }
          else if (tag_constant_2 != std::string::npos)
          {
            auto spot_light_node_ptr = dynamic_cast<SpotLightNode*>(node.get());
            spot_light_node_ptr->constant = stof(parse_single_string(line));
          }
          else if (tag_linear_2 != std::string::npos)
          {
            auto spot_light_node_ptr = dynamic_cast<SpotLightNode*>(node.get());
            spot_light_node_ptr->linear = stof(parse_single_string(line));
          } 
          else if (tag_quadratic_2 != std::string::npos)
          {
            auto spot_light_node_ptr = dynamic_cast<SpotLightNode*>(node.get());
            spot_light_node_ptr->quadratic = stof(parse_single_string(line));
          } 
          else if (tag_cut_off != std::string::npos)
          {
            auto spot_light_node_ptr = dynamic_cast<SpotLightNode*>(node.get());
            spot_light_node_ptr->cut_off = stof(parse_single_string(line));
          } 
          else if (tag_outer_cut_off != std::string::npos)
          {
            auto spot_light_node_ptr = dynamic_cast<SpotLightNode*>(node.get());
            spot_light_node_ptr->outer_cut_off = stof(parse_single_string(line));
          }
          else if (line_temp == "-") { }
          else
          {
            node = nullptr;
            parsing_node = false;
          }
        }
      }
    }

    /*
      Third Pass:
        - create relations
    */

    // set root
    scene->m_Sg.m_Root = find_node_in_vec(nodes, default_root_name);

    for (std::shared_ptr<Node> it : nodes)
    {
      for (unsigned int i = 0; i < nodes.size(); ++i)
      {
        if (it->m_Name == std::get<0>(nodes_config.at(i)))
        {
          // set children
          for (const std::string& str : std::get<2>(nodes_config.at(i)))
          {
            if (it->m_Name != str)
            {
              // addChild() automatically sets parent relations
              it->addChild(find_node_in_vec(nodes, str));
            }
          }
        }
      }
    }

    

    if (scene->m_Name == "__UNDEF__")
      return false;

    push(scene);
    MX_SUCCESS("MX: World: Load Scene: " + scene->m_Name + " Completed");
    return true;
  }
}