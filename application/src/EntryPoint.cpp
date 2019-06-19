#include <Matrix.h>

void initialize()
{
  MX::MX_WORLD.initialize();

  MX::MX_WORLD.push(std::shared_ptr<MX::Scene>(new MX::Scene("debug")));

  MX::MX_SCENE->push("Jupiter", "sphere.obj", "Root");
  MX::MX_SCENE->push("Saturn", "sphere.obj", "Jupiter");

  MX::MX_SCENE->push("Rock", "rock.obj", "Root");

  std::shared_ptr<MX::Node> jupiter = MX::MX_SCENEGRAPH.search("Jupiter", MX::MX_ROOT);
  jupiter->setTransform(MX::Y, 0.3f, 1);
  jupiter->setShader(MX_GET_SHADER("blinn_phong"));
  jupiter->setTexture(MX_GET_TEXTURE("2k_jupiter.jpg"));

  std::shared_ptr<MX::Node> saturn = MX::MX_SCENEGRAPH.search("Saturn", MX::MX_ROOT);
  saturn->setTransform(MX::SCALE, 0.4f, 0);
  saturn->setTransform(MX::Y, 0.8f, 1);
  saturn->setTransform(MX::RIGHT, 5.0f, 0);
  saturn->setShader(MX_GET_SHADER("blinn_phong"));
  saturn->setTexture(MX_GET_TEXTURE("2k_saturn.jpg"));

  std::shared_ptr<MX::Node> rock = MX::MX_SCENEGRAPH.search("Rock", MX::MX_ROOT);
  rock->setTransform(MX::SCALE, 0.05f, 0);
  rock->setTransform(MX::BACKWARDS, 35.0f, 0);
  rock->setTransform(MX::LEFT, 0.5f, 0);
  rock->setTransform(MX::Y, 0.8f, 1);
  rock->setTransform(MX::X, 0.5f, 1);
  rock->setShader(MX_GET_SHADER("phong"));
  rock->setTexture(MX_GET_TEXTURE("rock.jpg"));

}

void update()
{
  MX::MX_WORLD.update();
}

void render()
{
  MX::MX_WORLD.render();
}

int main()
{
  // application testing
  MX::Application::get().initialize(initialize);
  MX::Application::get().m_Window->setTitle("My Application");

  // rendering loop
  while (MX::Application::get().m_Running)
  {
    MX::Application::get().update(update);
    MX::Application::get().render(render);
  }
  MX::Application::get().clean();
  
  return 0;
}