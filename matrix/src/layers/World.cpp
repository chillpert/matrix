#include "World.h"
#include "Application.h"

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

namespace MX
{
  World::~World()
  {
    MX_INFO_LOG("MX: World: Destructor");
  }

  std::shared_ptr<Model> World::getModel(const std::string& path)
  {
    for (auto it : m_models)
    {
      if (it->m_full_path == path)
      {
        if (!it->m_initialized)
          it->initialize();
        MX_INFO_LOG("MX: World: GetModel: Model at " + path + " already exists. Continue using existing data instead.");
        return it;
      }
    }

    std::shared_ptr<Model> temp = std::make_shared<Model>(path, true);
    m_models.push_back(temp);
    MX_INFO_LOG("MX: World: GetModel: Created Model at " + path);
    return temp;
  }

  std::shared_ptr<Shader> World::getShader(const std::string& path)
  {
    for (auto it : m_shaders)
    {
      if (it->m_path == path)
      {
        if (!it->m_initialized)
          it->initialize();
        MX_INFO_LOG("MX: World: GetShader: Shader at " + path + " already exists. Continue using existing data instead.");
        return it;
      }
    }

    std::shared_ptr<Shader> temp = std::make_shared<MX_SHADER>(path, true);
    m_shaders.push_back(temp);
    MX_INFO_LOG("MX: World: GetShader: Created Shader at " + path);
    return temp;
  }

  std::shared_ptr<Texture> World::getTexture(const std::string& path, std::string& type)
  {
    for (auto it : m_textures)
    {
      if (it->m_path == path)
      {
        if (!it->m_initialized) 
          it->initialize();

        MX_INFO_LOG("MX: World: GetTexture: Texture at " + path + " already exists. Continue using existing data instead.");
        return it;
      }
    }

    std::shared_ptr<MX_TEXTURE> temp = std::make_shared<MX_TEXTURE>(path, true);
    temp->m_type = type;
    m_textures.push_back(temp);
    MX_INFO_LOG("MX: World: GetTexture: Created Texture at " + path);
    return temp;
  } 

  void World::initialize()
  {
    for (auto it : m_ExistingScenes)
    {
      if (it != nullptr)
        it->initialize();
    }
  }

  void World::update()
  {
    if (m_ActiveScene != nullptr)
      m_ActiveScene->update();
  }

  void World::render()
  {
    if (m_ActiveScene != nullptr)
      m_ActiveScene->render();
  }

  void World::push(std::shared_ptr<Scene> scene)
  {
    if (scene != nullptr)
    {
      bool accepted = true;
      for (const std::shared_ptr<Scene> it : m_ExistingScenes)
      {
        if (it->m_Name == scene->m_Name)
          accepted = false;
      }

      if (accepted)
      {
        m_ActiveScene = scene;
        m_ExistingScenes.push_back(scene);
        scene->initialize();
        MX_INFO_LOG("MX: World: Scene: " + scene->m_Name + ": Added");
        return;
      }
      
      uint64_t counter = 0;
      accepted = false;
      std::string current_name = scene->m_Name;
      std::string appendix = "";

      while (!accepted)
      {
        bool already_exists = false;
        for (const std::shared_ptr<Scene> it : m_ExistingScenes)
        {
          if (it->m_Name == current_name)
          {
            ++counter;
            appendix = "_" + std::to_string(counter);
            already_exists = true;
            break;
          }
        }

        if (!already_exists)
        {
          accepted = true;
        }
      }

      scene->m_Name += appendix;
      scene->initialize();
      m_ActiveScene = scene;
      m_ExistingScenes.push_back(scene);
      MX_INFO_LOG("MX: World: Scene: " + scene->m_Name + ": Added");
      return;
    }
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

  std::shared_ptr<Scene> World::getScene(const std::string& name)
  {
    for (std::shared_ptr<Scene> it : m_ExistingScenes)
    {
      if (it->m_Name == name)
        return it;
    }

    return nullptr;
  }
  
  bool World::load_scene(const std::string &name)
  {
    //remove_scene(name);

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
          auto tag_yaw = line_temp.find("@Yaw");
          auto tag_pitch = line_temp.find("@Pitch");
          auto tag_fov = line_temp.find("@FOV");
          auto tag_sensitivity = line_temp.find("@Sensitivity");

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
          else if (tag_yaw != std::string::npos)
          {
            auto bracket_l = line_temp.find("{");  
            scene->m_Cam.m_Yaw = stof(line_temp.substr(bracket_l + 1, line_temp.length() - bracket_l - 2));
          }
          else if (tag_pitch != std::string::npos)
          {
            auto bracket_l = line_temp.find("{");  
            scene->m_Cam.m_Pitch = stof(line_temp.substr(bracket_l + 1, line_temp.length() - bracket_l - 2));
          }
          else if (tag_fov != std::string::npos)
          {
            auto bracket_l = line_temp.find("{");  
            scene->m_Cam.m_Fov = stof(line_temp.substr(bracket_l + 1, line_temp.length() - bracket_l - 2));
          }
          else if (tag_sensitivity != std::string::npos)
          {
            auto bracket_l = line_temp.find("{");  
            scene->m_Cam.m_Sensitivity = stof(line_temp.substr(bracket_l + 1, line_temp.length() - bracket_l - 2));
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
          auto temp = std::make_shared<GeometryNode>(std::get<0>(it));
          nodes.push_back(temp);
          scene->m_objects.emplace(temp->m_Name, temp);
          scene->m_ExistingObjects.push_back(temp->m_Name);
          scene->m_Sg.m_object_nodes.push_back(temp);
          break;
        }
        case NodeType::type_container:
        {
          auto temp = std::make_shared<ContainerNode>(std::get<0>(it));
          nodes.push_back(temp);
          scene->m_objects.emplace(temp->m_Name, temp);
          scene->m_ExistingObjects.push_back(temp->m_Name);
          scene->m_Sg.m_container_nodes.push_back(temp);
          break;
        }
        case NodeType::type_light:
        {
          MX_FATAL("MX: World: Load Scene: Creation of a node of the light node class is not possible");
          break;
        }
        case NodeType::type_directionalLight:
        {
          auto temp = std::make_shared<DirectionalLightNode>(std::get<0>(it));
          nodes.push_back(temp);
          scene->m_ExistingObjects.push_back(temp->m_Name);
          scene->m_Sg.m_directional_light_nodes.push_back(temp);
          break;
        }
        case NodeType::type_spotLight:
        {
          auto temp = std::make_shared<SpotLightNode>(std::get<0>(it));
          nodes.push_back(temp);
          scene->m_ExistingObjects.push_back(temp->m_Name);
          scene->m_Sg.m_spot_light_nodes.push_back(temp);
          break;
        }
        case NodeType::type_pointLight:
        {
          auto temp = std::make_shared<PointLightNode>(std::get<0>(it));
          nodes.push_back(temp);
          scene->m_ExistingObjects.push_back(temp->m_Name);
          scene->m_Sg.m_point_light_nodes.push_back(temp);
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
            node->setShader(getShader(MX_ROOT_PATH + parse_single_string(line_temp)));
          }
          else if (tag_transform != std::string::npos)
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
            geometry_node_ptr->m_Model = getModel(MX_ROOT_PATH + parse_single_string(line_temp));
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

              if (temp_.at(0) == 'D' && temp_.at(1) == '{')
              {
                std::string texture_type = "texture_diffuse";
                textures.diffuse = getTexture(MX_ROOT_PATH + str, texture_type);
                continue;
              }
              else if (temp_.at(0) == 'S' && temp_.at(1) == '{')
              {
                std::string texture_type = "texture_specular";
                textures.specular = getTexture(MX_ROOT_PATH + str, texture_type);
                continue;
              }
              else if (temp_.at(0) == 'N' && temp_.at(1) == '{')
              {
                std::string texture_type = "texture_normal";
                textures.normal = getTexture(MX_ROOT_PATH + str, texture_type);
                continue;
              }
              else if (temp_.at(0) == 'B' && temp_.at(1) == '{')
              {
                std::string texture_type = "texture_bump";
                textures.bump = getTexture(MX_ROOT_PATH + str, texture_type);
                continue;
              }
              else if (temp_.at(0) == 'H' && temp_.at(1) == '{')
              {
                std::string texture_type = "texture_height";
                textures.height = getTexture(MX_ROOT_PATH + str, texture_type);
                continue;
              }
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

              if (temp_.at(0) == 'A' && temp_.at(1) == '{')
                geometry_node_ptr->m_material.ambient = parse_vec3(str);
              else if (temp_.at(0) == 'D' && temp_.at(1) == '{')
                geometry_node_ptr->m_material.diffuse = parse_vec3(str);
              else if (temp_.at(0) == 'S' && temp_.at(1) == '{')
                geometry_node_ptr->m_material.specular = parse_vec3(str);
              else if (temp_.at(0) == 's' && temp_.at(1) == '{')
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

    // reset file
    file.clear();
    file.seekg(0, file.beg);

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
    {
      MX_FATAL("MX: World: Load Scene: Error in naming");
      return false;
    }

    push(scene);

    MX_SUCCESS("MX: World: Load Scene: " + scene->m_Name + " Completed");
    return true;
  }

  bool World::remove_scene(const std::string &name)
  {
    for (std::vector<std::shared_ptr<Scene>>::iterator it = m_ExistingScenes.begin(); it != m_ExistingScenes.begin(); ++it)
    {
      if ((*it)->m_Name == name)
      {
        m_ExistingScenes.erase(it);
        return true; 
      }
    }

    return false;
  }

  bool World::remove_scene(const std::shared_ptr<Scene> scene)
  {
    for (std::vector<std::shared_ptr<Scene>>::iterator it = m_ExistingScenes.begin(); it != m_ExistingScenes.begin(); ++it)
    {
      if ((*it) == scene)
      {
        m_ExistingScenes.erase(it);
        return true;
      }
    }

    return false;
  }
}