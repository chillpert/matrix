#include "Matrix.h"

using namespace MX;

void initialize()
{
using namespace MX;

  MX_CAMERA.m_Position = {0.0f, 1.0f, 4.0f};

  //MX_SCENE->push_directional_light("Dir Light 1");
  MX_SCENE->push_point_light("Point Light 1");
  MX_SCENE->push_spot_light("Spot Light 1");

  TextureProfile floor_textures;
  floor_textures.diffuse = MX_GET_TEXTURE("diffuse/wood.png");
  floor_textures.specular = MX_GET_TEXTURE("specular/wood_specular.jpg");

  MX_SCENE->push_object_with_texture_profile("Floor", MX_GET_MODEL("quad.obj"), MX_GET_SHADER("blinn_phong"), floor_textures);
  auto floor_node = MX_SCENEGRAPH.search<GeometryNode>("Floor");
  floor_node->setTransform(SCALE, 2.0f, 0);
  floor_node->setTransform(X, 270.0f, 0);

  MX_SCENE->push_object("Box");
  auto box = MX_SCENEGRAPH.search<GeometryNode>("Box");
  box->m_Shader = MX_GET_SHADER("blinn_phong");
  box->m_Model = MX_GET_MODEL("cube.obj");
  box->m_textures->diffuse = MX_GET_TEXTURE("diffuse/box.png");
  box->m_textures->specular = MX_GET_TEXTURE("specular/box_specular.png");

  box->setTransform(Y, 60.0f, 0);

  box->setTransform(UP, 0.49f, 0);
  box->setTransform(LEFT, 1.5f, 0);
  box->setTransform(BACKWARDS, 0.5f, 0);

  TextureProfile wooden_chair;
  wooden_chair.diffuse = MX_GET_TEXTURE("diffuse/wood dark.jpg");
  wooden_chair.specular = MX_GET_TEXTURE("specular/wood_specular.jpg");

  MaterialProfile wooden_chair_material;
  wooden_chair_material.shininess = 4.0f;

  MX_SCENE->push_object_with_material_and_texture_profile("Chair Wood", MX_GET_MODEL("simple_chair/Chair.obj"), MX_GET_SHADER("blinn_phong"), wooden_chair_material, wooden_chair);
  auto chair = MX_SCENEGRAPH.search<GeometryNode>("Chair Wood");
  chair->setTransform(FORWARDS, 1.0f, 0);
  chair->setTransform(LEFT, 0.8f, 0);
  chair->setTransform(Y, 117.0f, 0);
}

void update()
{

}

void render()
{

}

int main()
{
  // application testing
  Application::get().initialize(initialize);

  // rendering loop
  while (Application::get().m_Running)
  {
    Application::get().update(update);
    Application::get().render(render);
  }
  Application::get().clean();

  return 0;
}