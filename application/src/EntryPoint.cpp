#include "Matrix.h"

void init_debug_scene()
{
  using namespace MX;

  MX_SCENE->push_container("Lighting");
  {
    MX_SCENE->push_directional_light("Directional Light 1", "Lighting");
    MX_SCENE->push_point_light("Point Light 1", "Lighting");

    // to see the flashlight you need to active it in outline
    MX_SCENE->push_spot_light("Spot Light 1", "Lighting");
  }

  MX_SCENE->push_object("Characters", default_root_name);
  {
    MX_SCENE->push_object("Prophet", MX_GET_MODEL("nanosuit_model/nanosuit.obj"), MX_GET_SHADER("blinn_phong"), "Characters");
    auto nano_suit = MX_SCENEGRAPH.search<Node>("Prophet");
  }

  MX_SCENE->push_container("Environment");
  {
    MX_SCENE->push_object_with_diffuse_texture("Rock 1", MX_GET_MODEL("rock.obj"), MX_GET_SHADER("blinn_phong"), MX_GET_TEXTURE("diffuse/rock.jpg"), "Environment");
    auto rock_1 = MX_SCENEGRAPH.search<Node>("Rock 1");

    MX_SCENE->push_object_with_diffuse_texture("Rock 2", MX_GET_MODEL("rock.obj"), MX_GET_SHADER("blinn_phong"), MX_GET_TEXTURE("diffuse/rock.jpg"), "Environment");
    auto rock_2 = MX_SCENEGRAPH.search<Node>("Rock 2");

    MX_SCENE->push_object_with_diffuse_texture("Rock 3", MX_GET_MODEL("rock.obj"), MX_GET_SHADER("blinn_phong"), MX_GET_TEXTURE("diffuse/rock.jpg"), "Environment");
    auto rock_3 = MX_SCENEGRAPH.search<Node>("Rock 3");

    MX_SCENE->push_container("Planets", "Environment");
    {
      MX_SCENE->push_object_with_diffuse_texture("Jupiter", MX_GET_MODEL("sphere.obj"), MX_GET_SHADER("blinn_phong"), MX_GET_TEXTURE("diffuse/2k_jupiter.jpg"), "Planets");
      auto jupiter = MX_SCENEGRAPH.search<Node>("Jupiter");

      {
        MX_SCENE->push_object_with_diffuse_texture("Saturn", MX_GET_MODEL("sphere.obj"), MX_GET_SHADER("blinn_phong"), MX_GET_TEXTURE("diffuse/2k_saturn.jpg"), "Jupiter");
        auto saturn = MX_SCENEGRAPH.search<Node>("Saturn");
      }
    }
  }

  MX_SUCCESS("MX: Debug Scene: Initialized");
}

void init_floor_scene()
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

  MX_SCENE->push_object("Box");
  auto box = MX_SCENEGRAPH.search<GeometryNode>("Box");
  box->m_Shader = MX_GET_SHADER("blinn_phong");
  box->m_Model = MX_GET_MODEL("cube.obj");
  box->m_textures->diffuse = MX_GET_TEXTURE("diffuse/box.png");
  box->m_textures->specular = MX_GET_TEXTURE("specular/box_specular.png");

  TextureProfile wooden_chair;
  wooden_chair.diffuse = MX_GET_TEXTURE("diffuse/wood dark.jpg");
  wooden_chair.specular = MX_GET_TEXTURE("specular/wood_specular.jpg");

  MaterialProfile wooden_chair_material;
  wooden_chair_material.shininess = 4.0f;

  MX_SCENE->push_object_with_material_and_texture_profile("Chair Wood", MX_GET_MODEL("simple_chair/Chair.obj"), MX_GET_SHADER("blinn_phong"), wooden_chair_material, wooden_chair);
  auto chair = MX_SCENEGRAPH.search<GeometryNode>("Chair Wood");

/*
  MX_SCENE->push_object("Plant", MX_GET_MODEL("table/table.obj"), MX_GET_SHADER("blinn_phong"));
  auto plant = MX_SCENEGRAPH.search<GeometryNode>("Plant");  
  //plant->setTransform(SCALE, 0.001f, 0);
  plant->setTransform(SCALE, 0.06f, 0);
  plant->setTransform(X, 3.1f, 0);
*/
}

void init_material_test_scene()
{
  using namespace MX;

  MX_SCENE->push_directional_light("Dir Light 1");
  auto dir_light = MX_SCENEGRAPH.search<DirectionalLightNode>("Dir Light 1");
  dir_light->ambient_strength = 1.0f;

  MaterialProfile emerald_profile;
  emerald_profile.ambient = {0.0215f, 0.1745f, 0.0215f};
  emerald_profile.diffuse = {0.07568f, 0.61424f, 0.07568f};
  emerald_profile.specular = {0.633f, 0.727811f, 0.633f};
  emerald_profile.shininess = {0.6f * 128.0f};

  TextureProfile emerald_texture_profile;
  emerald_texture_profile.diffuse = MX_GET_TEXTURE("diffuse/white.jpg");

  MX_SCENE->push_object_with_material_and_texture_profile("Emerald", MX_GET_MODEL("cube.obj"), MX_GET_SHADER("blinn_phong"), emerald_profile, emerald_texture_profile);
}

void initialize()
{
  using namespace MX;
  MX_WORLD.initialize();
  
/*
  MX_WORLD.push(std::make_shared<Scene>("Debug"));

#ifdef MX_DEBUG
  init_debug_scene();
#endif

  MX_WORLD.push(std::make_shared<Scene>("Materials"));

#ifdef MX_DEBUG
  init_material_test_scene();
#endif
*/
  MX_WORLD.push(std::make_shared<Scene>("My First Scene"));

#ifdef MX_DEBUG
  //init_floor_scene();
#endif
}

void update()
{
  using namespace MX;
  MX_WORLD.update();
}

void render()
{
  using namespace MX;
  MX_WORLD.render();
}

int main()
{
  // application testing
  MX::Application::get().initialize(initialize);

  // rendering loop
  while (MX::Application::get().m_Running)
  {
    MX::Application::get().update(update);
    MX::Application::get().render(render);
  }
  MX::Application::get().clean();
  
  return 0;
}