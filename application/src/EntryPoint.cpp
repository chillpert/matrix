#include <Matrix.h>

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
    auto nano_suit = MX_SCENEGRAPH.search("Prophet");
    nano_suit->setTransform(SCALE, 0.2f, 0);
    nano_suit->setTransform(DOWN, 3.5f, 0);
  }

  MX_SCENE->push_container("Environment");
  {
    MX_SCENE->push_object_with_diffuse_texture("Rock 1", MX_GET_MODEL("rock.obj"), MX_GET_SHADER("blinn_phong"), MX_GET_TEXTURE("rock.jpg"), "Environment");
    auto rock_1 = MX_SCENEGRAPH.search("Rock 1");
    rock_1->setTransform(SCALE, 0.05f, 0);
    rock_1->setTransform(BACKWARDS, 35.0f, 0);
    rock_1->setTransform(LEFT, 0.5f, 0);
    rock_1->setTransform(Y, 0.8f, 1);
    rock_1->setTransform(X, 0.5f, 1);

    MX_SCENE->push_object_with_diffuse_texture("Rock 2", MX_GET_MODEL("rock.obj"), MX_GET_SHADER("blinn_phong"), MX_GET_TEXTURE("rock.jpg"), "Environment");
    auto rock_2 = MX_SCENEGRAPH.search("Rock 2");
    rock_2->setTransform(SCALE, 0.15f, 0);
    rock_2->setTransform(FORWARDS, 35.0f, 0);
    rock_2->setTransform(LEFT, 0.5f, 0);
    rock_2->setTransform(Z, 0.8f, 1);
    rock_2->setTransform(Y, 0.5f, 1);

    MX_SCENE->push_object_with_diffuse_texture("Rock 3", MX_GET_MODEL("rock.obj"), MX_GET_SHADER("blinn_phong"), MX_GET_TEXTURE("rock.jpg"), "Environment");
    auto rock_3 = MX_SCENEGRAPH.search("Rock 3");
    rock_3->setTransform(SCALE, 0.55f, 0);
    rock_3->setTransform(LEFT, 4.5f, 0);
    rock_3->setTransform(Z, 0.8f, 1);

    MX_SCENE->push_container("Planets", "Environment");
    {
      MX_SCENE->push_object_with_diffuse_texture("Jupiter", MX_GET_MODEL("sphere.obj"), MX_GET_SHADER("blinn_phong"), MX_GET_TEXTURE("2k_jupiter.jpg"), "Planets");
      auto jupiter = MX_SCENEGRAPH.search("Jupiter");
      jupiter->setTransform(Y, 0.3f, 1);

      {
        MX_SCENE->push_object_with_diffuse_texture("Saturn", MX_GET_MODEL("sphere.obj"), MX_GET_SHADER("blinn_phong"), MX_GET_TEXTURE("2k_saturn.jpg"), "Jupiter");
        auto saturn = MX_SCENEGRAPH.search("Saturn");
        saturn->setTransform(SCALE, 0.4f, 0);
        saturn->setTransform(Y, 0.8f, 1);
        saturn->setTransform(RIGHT, 5.0f, 0);
      }
    }
  }

  MX_SUCCESS("MX: Debug Scene: Initialized");
}

void init_material_test_scene()
{
  using namespace MX;

}

void init_floor_scene()
{
  using namespace MX;

  //MX_SCENE->push_directional_light("Dir Light 1");
  MX_SCENE->push_point_light("Point Light 1");
  //MX_SCENE->push_spot_light("Spot Light 1");

  MX_SCENE->push_object_with_diffuse_texture("Floor", MX_GET_MODEL("quad.obj"), MX_GET_SHADER("blinn_phong"), MX_GET_TEXTURE("wood.png"));
  auto floor_node = MX_SCENEGRAPH.search("Floor", type_geometry);
  floor_node->setTransform(SCALE, 2.0f, 0);
  //floor_node->setTransform(X, 1.5f, 0);
  //floor_node->setTransform(DOWN, 3.5f, 0);
}

void initialize()
{
  using namespace MX;

  MX_WORLD.initialize();
  MX_WORLD.push(std::shared_ptr<Scene>(new Scene("debug")));

#ifdef MX_DEBUG
  init_debug_scene();
#endif

  MX_WORLD.push(std::shared_ptr<Scene>(new Scene("material test")));

#ifdef MX_DEBUG
  init_material_test_scene();
#endif

  MX_WORLD.push(std::shared_ptr<Scene>(new Scene("floor")));

#ifdef MX_DEBUG
  init_floor_scene();
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