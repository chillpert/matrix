#include "matrix/src/layers/Scene.h"
#include "matrix/src/layers/World.h"
#include "matrix/src/Application.h"

namespace MX
{
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

  // adds object to scene graph
  void Scene::push(const std::string &object_name, const std::string &file_name, const std::string &node_to_attach_to)
  {
    bool modelExists = 0;
    bool shaderExists = 0;
    bool textureExists = 0;

    Node *temp_node;
    MX_MODEL *temp_model;
    MX_SHADER *temp_shader;
    MX_TEXTURE *temp_texture;

    /*############################
    check if element already exist
    ############################*/

    // model
  #ifndef MX_INSTANT_MODEL_INIT
    for (auto *it : World::get().m_Models)
    {
      if (it->getName() == file_name)
      {
        MX_INFO_LOG("MX: Model Handler: Object already exists: Continue without parsing");
        modelExists = 1;
        temp_model = it;
        break;
      }
    }
  #endif
    if (!modelExists)
    {
      MX_INFO_LOG("MX: Model Handler: Object does not exist: Continue with parsing");
      temp_model = new MX_MODEL(file_name, 1);
      World::get().m_Models.push_back(temp_model);
    }

/*
    // shader
  #ifndef MX_INSTANT_SHADER_INIT
    for (auto *it : World::get().m_Shaders)
    {
      if (it->getName() == )
      {
        MX_INFO_LOG("MX: Shader: Already exist: Continue without initialization");
        shaderExists = 1;
        temp_shader = it;
        break;
      }
    }
  #endif

    if (!shaderExists)
    {
      MX_INFO_LOG("MX: Shader: Continue initialization");
      temp_shader = new MX_SHADER(, 1);
      World::get().m_Shaders.push_back(temp_shader);
    }

    // texture
  #ifndef MX_INSTANT_TEXTURE_INIT
    for (auto *it : World::get().m_Textures)
    {
      if (it->getName() == )
      {
        MX_INFO_LOG("MX: Shader: Already exist: Continue without initialization");
        textureExists = 1;
        temp_texture = it;
        break;
      }
    }
  #endif

    if (!textureExists)
    {
      MX_INFO_LOG("MX: Shader: Continue initialization");
      temp_texture = new MX_TEXTURE(, 1);
      World::get().m_Shaders.push_back(temp_shader);
    }
*/
  #ifdef MX_DEBUG
    // get memory address
    std::ostringstream address;
    address << temp_node;
    std::string address_s =  address.str(); 
    MX_INFO_LOG("MX: Scene: " + m_Name + ": Push: " + object_name + ": Address: " + address_s);
  #endif

    // create node
    temp_node = new Node(object_name, temp_model, World::get().m_Shaders.at(0), nullptr);
    // find node to attach new node to
    m_Sg.recursive_search(node_to_attach_to, m_Sg.m_Root);
    // attach new nede
    search_holder->addChild(temp_node);

    MX_SUCCESS_LOG("MX: Scene: Push: " + object_name);
  }

  // delete object from scene graph
  void Scene::pop(const std::string &name)
  {
  #ifdef MX_DEBUG
    m_Sg.recursive_search(name, m_Sg.m_Root);

    std::ostringstream address; 
    address << search_holder;
    std::string address_s =  address.str();
    MX_INFO_LOG("MX: Scene: " + m_Name + ": Pop: Trying to pop: " + search_holder->m_Name + ": Adress: " + address_s);
  #endif              
    m_Sg.iterative_delete(name);

    MX_SUCCESS_LOG("MX: Scene: " + m_Name + ": Pop: " + name);
  }
}