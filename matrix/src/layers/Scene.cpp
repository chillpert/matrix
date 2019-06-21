#include <Scene.h>
#include <World.h>
#include <Application.h>

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
    
  }

  void Scene::update()
  {
    m_Cam.update();
  }

  void Scene::render()
  {
    m_Sg.render();
  }

  bool Scene::push(std::shared_ptr<Node> node, std::shared_ptr<Node> node_to_attach_to)
  {
    if (!object_already_exists(node->m_Name))
    {
      m_ExistingObjects.push_back(node->m_Name);
      return 1;
    }
    else
      return 0;

    node_to_attach_to->addChild(std::shared_ptr<Node>(node));
  }

  bool Scene::push(const std::string &name, const std::string &node_to_attach_to)
  {
    push(name, nullptr, nullptr, nullptr, node_to_attach_to);
  }

  bool Scene::push(const std::string &name, std::shared_ptr<Model> model, const std::string &node_to_attach_to)
  {
    push(name, model, nullptr, nullptr, node_to_attach_to);
  }

  bool Scene::push(const std::string &name, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, const std::string &node_to_attach_to)
  {
    push(name, model, shader, nullptr, node_to_attach_to);
  }

  bool Scene::push(const std::string &name, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, const std::string &node_to_attach_to)
  {
    MX_INFO_LOG("MX: Scene: " + m_Name + " Push: " + name);

    if (!object_already_exists(name))
      m_ExistingObjects.push_back(name);
    else
    {
      MX_WARN("MX: Scene: " + m_Name + " Push: " + name + ": Invalid name - object already exists");
      return 0;
    }

    std::shared_ptr<Node> temp(new Node(name));
    temp->setModel(model);
    temp->setShader(shader);
    temp->setTexture(texture);

    MX_SCENEGRAPH.search(node_to_attach_to, MX_ROOT)->addChild(temp);
    MX_SUCCESS_LOG("MX: Scene: "  + m_Name + " Push: " + name);
    return 1;
  }

  // delete object from scene graph
  bool Scene::pop(const std::string &name)
  {
    std::shared_ptr<Node> temp_node = m_Sg.search(name, m_Sg.m_Root);

  #ifdef MX_DEBUG
    std::ostringstream address;
    address << temp_node;
    std::string address_s =  address.str();
    MX_INFO_LOG("MX: Scene: " + m_Name + "Pop: Node: " + temp_node->m_Name + ": Address: " + address_s);
  #endif

    for (auto iter = temp_node->m_Parent->m_Children.begin(); iter != temp_node->m_Parent->m_Children.end(); ++iter)
    {
      if ((*iter)->m_Name == temp_node->m_Name)
      {
        temp_node->m_Parent->m_Children.erase(iter);
        MX_SUCCESS_LOG("MX: Scene: Pop");
        return 1;
      }
    }

    MX_FATAL("MX: Scene: " + m_Name + "Pop: Node: " + temp_node->m_Name + ": Address: " + address_s);
    return 0;
  }
}