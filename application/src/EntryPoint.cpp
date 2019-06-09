#include "matrix/Matrix.h"

void initialize()
{
  MX::World::get().initialize();

  MX::World::get().push(new MX::Scene("debug"));

#ifndef MX_IMGUI_ACTIVE
  MX::World::get().m_ActiveScene->push("debug node", "sphere.obj", "root");
#endif

  // default setup
  MX_SCENE->push("Jupiter", "sphere.obj", "root");
  MX_SCENE->push("Saturn", "sphere.obj", "Jupiter");
  MX_SCENE->push("Rock", "rock.obj", "root");

  

  MX::Node *jupiter = MX_SCENEGRAPH.search("Jupiter", MX_ROOT);
  jupiter->setTransform(MX::Y, 0.3f, 1);
  jupiter->setShader(MX_GET_SHADER("blinn_phong"));
  jupiter->setTexture(MX_GET_TEXTURE("2k_jupiter.jpg", 1));

  MX::Node *saturn = MX_SCENEGRAPH.search("Saturn", MX_ROOT);
  saturn->setTransform(MX::SCALE, 0.4f, 0);
  saturn->setTransform(MX::RIGHT, 5.0f, 0);
  saturn->setShader(MX_GET_SHADER("blinn_phong"));
  saturn->setTexture(MX_GET_TEXTURE("2k_saturn.jpg", 1));  

  MX::Node *rock = MX_SCENEGRAPH.search("Rock", MX_ROOT);
  rock->setTransform(MX::SCALE, 0.05f, 0);
  rock->setTransform(MX::BACKWARDS, 35.0f, 0);
  rock->setTransform(MX::LEFT, 0.5f, 0);
  rock->setShader(MX_GET_SHADER("phong"));
  rock->setTexture(MX_GET_TEXTURE("rock.jpg", 1));
}

void update()
{
  MX::World::get().update();
}

void render()
{
  MX::World::get().render();
}

int main()
{
  // application testing
  MX::Application::get().initialize(initialize);
  MX::Application::get().m_Window->setTitle("My Application");

  // rendering loop
  while(MX::Application::get().m_Running)
  {
    MX::Application::get().update(update);
    MX::Application::get().render(render);
  }
  MX::Application::get().clean();
  
  return 0;
}