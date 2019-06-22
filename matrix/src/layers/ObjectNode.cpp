#include <ObjectNode.h>

namespace MX
{
  ObjectNode::ObjectNode(const std::string &name)
    : Node(name) { }

  void ObjectNode::upload_uniforms()
  {
    Node::upload_uniforms();

    if (m_textures->diffuse != nullptr)
    {
      m_Shader->setInt("material.diffuse_texture1", 0);
      m_textures->diffuse->use();
    }
    
    if (m_textures->normal != nullptr)
    {
      m_Shader->setInt("material.normal_texture1", 1);
      m_textures->normal->use();
    }
    
    if (m_textures->bump != nullptr)
    {
      m_Shader->setInt("material.bump_texture1", 2);
      m_textures->bump->use();
    }
    
    if (m_textures->height != nullptr)
    {
      m_Shader->setInt("material.height_texture1", 3);
      m_textures->height->use();
    }

    m_Shader->setFloat("material.shininess", m_textures->shininess);

    if (m_Model != nullptr)
      m_Model->render(std::static_pointer_cast<MX_SHADER>(m_Shader));
  }

  void ObjectNode::setTextureProfile(std::shared_ptr<TextureProfile> texture)
  {
    if (texture != nullptr)
    {
      if (texture->diffuse != nullptr)
      {
        if (!texture->diffuse->m_initialized)
          texture->diffuse->initialize();

        if (!texture->normal->m_initialized)
          texture->normal->initialize();

        if (!texture->bump->m_initialized)
          texture->bump->initialize();

        if (!texture->height->m_initialized)
          texture->height->initialize();
        
        m_textures->diffuse = texture->diffuse;
        m_textures->normal = texture->normal;
        m_textures->bump = texture->bump;
        m_textures->height = texture->height;
      }
    }
  }

  void ObjectNode::setDiffuseTexture(std::shared_ptr<Texture> diffuse)
  {
    if (diffuse != nullptr)
    {
      diffuse->initialize();
      m_textures->diffuse = diffuse;
    }
  }

  void ObjectNode::setNormalTexture(std::shared_ptr<Texture> normal)
  {
    if (normal != nullptr)
    {
      normal->initialize();
      m_textures->normal = normal;
    }
  }

  void ObjectNode::setBumpTexture(std::shared_ptr<Texture> bump)
  {
    if (bump != nullptr)
    {
      bump->initialize();
      m_textures->bump = bump;
    }
  }

  void ObjectNode::setHeightTexture(std::shared_ptr<Texture> height)
  {
    if (height != nullptr)
    {
      height->initialize();
      m_textures->height = height;
    }
  }

  void ObjectNode::setModel(std::shared_ptr<Model> model)
  {
    if (model != nullptr)
    {
      if (!model->m_initialized)
        model->initialize();
    
      m_Model = model;
    }
    else
      m_Model = nullptr;
  }
}