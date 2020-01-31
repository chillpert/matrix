#include "Model.h"

namespace MX
{
  unsigned int load_texture(const std::string &path, const std::string &directory);

  Model::Model(const std::string &path, bool instant_init, bool gamma)
    : m_gamma_correction(gamma)
  {
    m_name = path.substr(path.find_last_of("/") + 1);
    m_full_path = path;
    m_relative_path = path.substr(path.find(std::string("matrix")) + 7); // 7 = m + a + t + r + i + x + /
    m_directory = m_full_path.substr(0, m_full_path.find_last_of('/'));

    if (instant_init)
      initialize();
  }

  void Model::initialize()
  {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(m_full_path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
      MX_FATAL("MX: Assimp: " + *importer.GetErrorString());
      return;
    }

    process_node(scene->mRootNode, scene);

    m_initialized = 1;
  }

  void Model::process_node(aiNode *node, const aiScene *scene)
  {
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
      aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
      m_meshes.push_back(process_mesh(mesh, scene));
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
      process_node(node->mChildren[i], scene);
    }
  }

  void Model::render(std::shared_ptr<Shader> shader)
  {
    for(unsigned int i = 0; i < m_meshes.size(); i++)
      m_meshes[i]->render_mesh(shader);
  }

  std::shared_ptr<Mesh> Model::process_mesh(aiMesh *mesh, const aiScene *scene)
  {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<Texture>> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
      Vertex vertex;
      glm::vec3 vector;

      // positions
      vector.x = mesh->mVertices[i].x;
      vector.y = mesh->mVertices[i].y;
      vector.z = mesh->mVertices[i].z;
      vertex.position = vector;

      // normals
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.normal = vector;

      // texture coordinates
      if(mesh->mTextureCoords[0])
      {
        glm::vec2 vec;
        vec.x = mesh->mTextureCoords[0][i].x; 
        vec.y = mesh->mTextureCoords[0][i].y;
        vertex.tex_coords = vec;
      }
      else
        vertex.tex_coords = glm::vec2(0.0f, 0.0f);

      // tangent
      vector.x = mesh->mTangents[i].x;
      vector.y = mesh->mTangents[i].y;
      vector.z = mesh->mTangents[i].z;
      vertex.tangent = vector;

      // bitangent
      vector.x = mesh->mBitangents[i].x;
      vector.y = mesh->mBitangents[i].y;
      vector.z = mesh->mBitangents[i].z;
      vertex.bitangent = vector;
      vertices.push_back(vertex);
    }

    // iterate through each mesh's face and retrieve correspoding vertex indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
      aiFace face = mesh->mFaces[i];
      for(unsigned int j = 0; j < face.mNumIndices; j++)
          indices.push_back(face.mIndices[j]);
    }

    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];    

    std::vector<std::shared_ptr<Texture>> diffuseMaps = load_material_texture(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<std::shared_ptr<Texture>> specularMaps = load_material_texture(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector<std::shared_ptr<Texture>> normalMaps = load_material_texture(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<std::shared_ptr<Texture>> heightMaps = load_material_texture(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return std::static_pointer_cast<Mesh>(std::make_shared<MX_MESH>(vertices, indices, textures));
  }

  std::vector<std::shared_ptr<Texture>> Model::load_material_texture(aiMaterial *mat, aiTextureType type, std::string typeName)
  {
    std::vector<std::shared_ptr<Texture>> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
      aiString str;
      mat->GetTexture(type, i, &str);
      // check if texture was loaded before, if so then skip
      bool skip = false;
      for (unsigned int j = 0; j < textures_loaded.size(); j++)
      {
        if (std::strcmp(textures_loaded[j]->m_path.data(), str.C_Str()) == 0)
        {
          textures.push_back(textures_loaded[j]);
          skip = true;
          break;
        }
      }
      if (!skip)
      {
        std::shared_ptr<MX_TEXTURE> texture = std::make_shared<MX_TEXTURE>(m_directory + '/' + str.C_Str());
        texture->m_type = typeName;
        texture->initialize();

        textures.push_back(texture);
        textures_loaded.push_back(texture);
      }
    }
    return textures;
  }

  unsigned int load_texture(const std::string &path, const std::string &directory)
  {
    std::string filename = directory + '/' + path;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
      GLenum format;
      if (nrComponents == 1)
        format = GL_RED;
      else if (nrComponents == 3)
        format = GL_RGB;
      else if (nrComponents == 4)
        format = GL_RGBA;

    #ifdef MX_OPENGL_ACTIVE
      glBindTexture(GL_TEXTURE_2D, textureID);
      glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    #elif MX_DIRECTX_ACTIVE

    #endif

      stbi_image_free(data);
    }
    else
    {
      MX_FATAL("MX: Texture: Failed to load path: " + path);
      stbi_image_free(data);
    }
    return textureID;
  }

}