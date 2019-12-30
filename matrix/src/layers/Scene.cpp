#include "Scene.h"
#include "World.h"
#include "Application.h"

namespace MX
{
  Scene::Scene(const std::string &name)
    : m_Name(name) { }

  Scene::~Scene()
  {
    MX_INFO_LOG("MX: Scene: Destructor");
  }

  bool Scene::object_already_exists(const std::string &name)
  {
    if (name == "")
      return 1;

    if (name == m_Sg.m_Root->m_Name)
      return 1;

    for (const std::string &it : m_ExistingObjects)
    {
      if (it == name)
        return 1;
    }

    return 0;
  }

  void Scene::initialize()
  {
    m_Sg.initialize();
  }

  void Scene::update()
  {
    m_Cam.update();
  }

  void Scene::render()
  {
    m_Sg.render();
  }

  /*###########################################################################################################################
  ######################################           PUSH ARBITRARY             #################################################
  ###########################################################################################################################*/

  bool Scene::push(std::shared_ptr<Node> node, std::shared_ptr<Node> node_to_attach_to)
  {
    if (!object_already_exists(node->m_Name))
    {
      m_ExistingObjects.push_back(node->m_Name);
      node_to_attach_to->addChild(std::shared_ptr<Node>(node));
      return 1;
    }

    return 0;
  }

  /*###########################################################################################################################
  ######################################             CONTAINER                #################################################
  ###########################################################################################################################*/

  bool Scene::push_container(const std::string &name, const std::string &node_to_attach_to)
  {
    MX_INFO("MX: Scene: " + m_Name + " Push Container: " + name);

    if (!object_already_exists(name))
      m_ExistingObjects.push_back(name);
    else
    {
      MX_WARN("MX: Scene: " + m_Name + " Push Container: " + name + ": Invalid name - object already exists");
      return 0;
    }

    std::shared_ptr<ContainerNode> container_node = std::make_shared<ContainerNode>(name);
    MX_SCENEGRAPH.search<Node>(node_to_attach_to)->addChild(std::static_pointer_cast<Node>(container_node));
    MX_SUCCESS("MX: Scene: "  + m_Name + " Push Container: " + name);
    return 1;
  }

  /*###########################################################################################################################
  #######################################             OBJECTS                ##################################################
  ###########################################################################################################################*/

  bool Scene::push_object(const std::string &name, const std::string &node_to_attach_to)
  {
    return push_object_with_texture_profile(name, nullptr, nullptr, TextureProfile(), node_to_attach_to);
  }

  bool Scene::push_object(const std::string &name, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, const std::string &node_to_attach_to)
  {
    return push_object_with_texture_profile(name, model, shader, TextureProfile(), node_to_attach_to);
  }

  bool Scene::push_object_with_diffuse_texture(const std::string &name, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, const std::string &node_to_attach_to)
  {
    MX_INFO("MX: Scene: " + m_Name + " Push Object: " + name);

    if (!object_already_exists(name))
      m_ExistingObjects.push_back(name);
    else
    {
      MX_WARN("MX: Scene: " + m_Name + " Push Object: " + name + ": Invalid name - object already exists");
      return 0;
    }

    std::shared_ptr<GeometryNode> object_node = std::make_shared<GeometryNode>(name);
    object_node->setModel(model);
    object_node->setShader(shader);
    object_node->setDiffuseTexture(texture);

    std::shared_ptr<Node> temp = std::static_pointer_cast<Node>(object_node);
    MX_SCENEGRAPH.search<Node>(node_to_attach_to)->addChild(temp);
    m_objects.emplace(temp->m_Name, temp);
    MX_SUCCESS("MX: Scene: "  + m_Name + " Push Object: " + name);
    return 1;
  }

  bool Scene::push_object_with_texture_profile(const std::string &name, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, const TextureProfile &texture_profile, const std::string &node_to_attach_to)
  {
    MX_INFO("MX: Scene: " + m_Name + " Push Object: " + name);

    if (!object_already_exists(name))
      m_ExistingObjects.push_back(name);
    else
    {
      MX_WARN("MX: Scene: " + m_Name + " Push Object: " + name + ": Invalid name - object already exists");
      return 0;
    }

    std::shared_ptr<GeometryNode> object_node = std::make_shared<GeometryNode>(name);
    object_node->setModel(model);
    object_node->setShader(shader);
    object_node->setTextureProfile(texture_profile);

    std::shared_ptr<Node> temp = std::static_pointer_cast<Node>(object_node);
    MX_SCENEGRAPH.search<Node>(node_to_attach_to)->addChild(temp);
    m_objects.emplace(temp->m_Name, temp);
    MX_SUCCESS("MX: Scene: "  + m_Name + " Push Object: " + name);
    return 1;
  }

  bool Scene::push_object_with_material_profile(const std::string &name, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, const MaterialProfile &material_profile, const std::string &node_to_attach_to)
  {
    MX_INFO("MX: Scene: " + m_Name + " Push Object: " + name);

    if (!object_already_exists(name))
      m_ExistingObjects.push_back(name);
    else
    {
      MX_WARN("MX: Scene: " + m_Name + " Push Object: " + name + ": Invalid name - object already exists");
      return 0;
    }

    std::shared_ptr<GeometryNode> object_node = std::make_shared<GeometryNode>(name);
    object_node->setModel(model);
    object_node->setShader(shader);
    object_node->setMaterialProfile(material_profile);

    std::shared_ptr<Node> temp = std::static_pointer_cast<Node>(object_node);
    MX_SCENEGRAPH.search<Node>(node_to_attach_to)->addChild(temp);
    m_objects.emplace(temp->m_Name, temp);
    MX_SUCCESS("MX: Scene: "  + m_Name + " Push Object: " + name);
    return 1;
  }

  bool Scene::push_object_with_material_and_texture_profile(const std::string &name, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, const MaterialProfile &material_profile, const TextureProfile &texture_profile, const std::string &node_to_attach_to)
  {
    MX_INFO("MX: Scene: " + m_Name + " Push Object: " + name);

    if (!object_already_exists(name))
      m_ExistingObjects.push_back(name);
    else
    {
      MX_WARN("MX: Scene: " + m_Name + " Push Object: " + name + ": Invalid name - object already exists");
      return 0;
    }

    std::shared_ptr<GeometryNode> object_node = std::make_shared<GeometryNode>(name);
    object_node->setModel(model);
    object_node->setShader(shader);
    object_node->setTextureProfile(texture_profile);
    object_node->setMaterialProfile(material_profile);

    std::shared_ptr<Node> temp = std::static_pointer_cast<Node>(object_node);
    MX_SCENEGRAPH.search<Node>(node_to_attach_to)->addChild(temp);
    m_objects.emplace(temp->m_Name, temp);
    MX_SUCCESS("MX: Scene: "  + m_Name + " Push Object: " + name);
    return 1;
  }

  /*###########################################################################################################################
  #######################################             LIGHTS                ###################################################
  ###########################################################################################################################*/

  bool Scene::push_directional_light(const std::string &name, const std::string &node_to_attach_to)
  {
    MX_INFO("MX: Scene: " + m_Name + " Push Directional Light: " + name);

    if (!object_already_exists(name))
      m_ExistingObjects.push_back(name);
    else
    {
      MX_WARN("MX: Scene: " + m_Name + " Push Directional Light: " + name + ": Invalid name - object already exists");
      return 0;
    }

    std::shared_ptr<DirectionalLightNode> light_node = std::make_shared<DirectionalLightNode>(name);
    light_node->setShader(MX_GET_SHADER("blinn_phong"));

    MX_SCENEGRAPH.m_directional_light_nodes.push_back(light_node);
    std::shared_ptr<Node> temp = std::static_pointer_cast<Node>(light_node);
    MX_SCENEGRAPH.search<Node>(node_to_attach_to)->addChild(temp);

    MX_SUCCESS("MX: Scene: "  + m_Name + " Push Directional Light: " + name);
    return 1;
  }

  bool Scene::push_point_light(const std::string &name, const std::string &node_to_attach_to)
  {
    MX_INFO("MX: Scene: " + m_Name + " Push Point Light: " + name);

    if (!object_already_exists(name))
      m_ExistingObjects.push_back(name);
    else
    {
      MX_WARN("MX: Scene: " + m_Name + " Push Point Light: " + name + ": Invalid name - object already exists");
      return 0;
    }

    std::shared_ptr<PointLightNode> light_node = std::make_shared<PointLightNode>(name);
    light_node->setShader(MX_GET_SHADER("blinn_phong"));

    MX_SCENEGRAPH.m_point_light_nodes.push_back(light_node);
    std::shared_ptr<Node> temp = std::static_pointer_cast<Node>(light_node);
    MX_SCENEGRAPH.search<Node>(node_to_attach_to)->addChild(temp);

    MX_SUCCESS("MX: Scene: "  + m_Name + " Push Point Light: " + name);
    return 1;
  }

  bool Scene::push_spot_light(const std::string &name, const std::string &node_to_attach_to)
  {
    MX_INFO("MX: Scene: " + m_Name + " Push Spot Light: " + name);

    if (!object_already_exists(name))
      m_ExistingObjects.push_back(name);
    else
    {
      MX_WARN("MX: Scene: " + m_Name + " Push Spot Light: " + name + ": Invalid name - object already exists");
      return 0;
    }

    std::shared_ptr<SpotLightNode> light_node = std::make_shared<SpotLightNode>(name);
    light_node->setShader(MX_GET_SHADER("blinn_phong"));

    MX_SCENEGRAPH.m_spot_light_nodes.push_back(light_node);
    std::shared_ptr<Node> temp = std::static_pointer_cast<Node>(light_node);
    MX_SCENEGRAPH.search<Node>(node_to_attach_to)->addChild(temp);

    MX_SUCCESS("MX: Scene: "  + m_Name + " Push Spot Light: " + name);
    return 1;
  }

  /*###########################################################################################################################
  #######################################               POP                 ###################################################
  ###########################################################################################################################*/

  // delete object from scene graph
  bool Scene::pop(const std::string &name)
  {
    m_objects.erase(name);

    std::shared_ptr<Node> temp_node = m_Sg.search<Node>(name);

  #ifdef MX_DEBUG
    std::ostringstream address;
    address << temp_node;
    std::string address_s =  address.str();
    MX_INFO("MX: Scene: " + m_Name + "Pop: Node: " + temp_node->m_Name + ": Address: " + address_s);
  #endif

    for (auto iter = temp_node->m_Parent->m_Children.begin(); iter != temp_node->m_Parent->m_Children.end(); ++iter)
    {
      if ((*iter)->m_Name == temp_node->m_Name)
      {
        temp_node->m_Parent->m_Children.erase(iter);
        MX_SUCCESS("MX: Scene: Pop");
        return 1;
      }
    }

    MX_FATAL("MX: Scene: " + m_Name + "Pop: Node: " + temp_node->m_Name + ": Address: " + address_s);
    return 0;
  }

  void Scene::save()
  {
    std::stringstream ss;

    // name @Name
    std::string name = "Scene";
    ss << name << "\n@Name{" << m_Name << "}" << std::endl;
    name = ss.str();
    ss.str("");

    // camera @Position @Front
    std::string camera = "\nCamera";
    ss << camera << "\n@Position{" << glm::to_string(m_Cam.m_Position) << "}\n@Front{" << glm::to_string(m_Cam.m_Front) << "}" << std::endl;;
    camera = ss.str();
    ss.str("");

    std::vector<std::shared_ptr<Node>> all_objects;
    all_objects.reserve(100);
    m_Sg.get_all_objects(all_objects, m_Sg.m_Root);
    std::reverse(all_objects.begin(), all_objects.end());

    std::string nodes = "Nodes\n";
    
    for (const std::shared_ptr<Node> it : all_objects)
      ss << it->to_string();

    ss << std::endl;
    nodes = ss.str();
    ss.str("");

    // write to file
    std::ofstream file;
    file.open(MX_SCENES_PATH + m_Name + ".mx");
    file << name << camera << nodes;
    file.close();
  }

  void Scene::remove()
  {

  }
}