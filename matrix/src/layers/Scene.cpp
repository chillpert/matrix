#include "matrix/src/layers/Scene.h"
#include "matrix/src/layers/World.h"
#include "matrix/src/Application.h"

namespace MX
{
  bool Scene::object_already_exists(const std::string &name)
  {
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

  bool Scene::push(const std::string &name)
  {
    if (!object_already_exists(name))
    {
      std::shared_ptr<Node> node = std::shared_ptr<Node>(new Node(name));
      m_Sg.m_Root->addChild(node);
      m_ExistingObjects.push_back(name);
      return 1;
    }
    
    return 0;
  }

  // adds object to scene graph
  bool Scene::push(const std::string &object_name, const std::string &file_name, const std::string &node_to_attach_to)
  {
    if (!object_already_exists(object_name))
      m_ExistingObjects.push_back(object_name);
    else
      return 0;

    std::shared_ptr<MX_MODEL> temp(new MX_MODEL(file_name));
    temp->initialize();
    World::get().m_Models.push_back(temp);

    std::shared_ptr<Node> temp_node_to_attach_to = m_Sg.search(node_to_attach_to, m_Sg.m_Root);
    
    temp_node_to_attach_to->addChild(std::shared_ptr<Node>(new Node(object_name, temp, World::get().getShader("blinn_phong"), nullptr)));
    
    MX_SUCCESS_LOG("MX: Scene: Push: " + object_name);
    return 1;
  }

  // delete object from scene graph
  bool Scene::pop(const std::string &name)
  {
  #ifdef MX_DEBUG
    try
    {
      std::shared_ptr<Node> temp_node = m_Sg.search(name, m_Sg.m_Root);
      std::ostringstream address;
      address << temp_node;
      std::string address_s =  address.str();
      MX_INFO_LOG("MX: Scene: " + m_Name + ": Pop: Trying to pop: " + temp_node->m_Name + ": Adress: " + address_s);
    }
    catch (const std::exception &e)
    {
      return 0;
    }
    
  #endif
    m_Sg.iterative_delete(name);

    MX_SUCCESS_LOG("MX: Scene: " + m_Name + ": Pop: " + name);
    return 1;
  }
}