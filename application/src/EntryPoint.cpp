#include "matrix/Matrix.h"

void initialize()
{
  MX::World::get().initialize();

  MX::World::get().push(new MX::Scene("debug"));

#ifndef MX_IMGUI_ACTIVE
  MX::World::get().m_ActiveScene->push("debug node", "sphere.obj", "root");
#endif

// default setup
  MX::World::get().m_ActiveScene->push("Jupiter", "sphere.obj", "root");
  MX::World::get().m_ActiveScene->push("Saturn", "sphere.obj", "Jupiter");
  MX::World::get().m_ActiveScene->push("Rock", "rock.obj", "root");

  MX::World::get().m_ActiveScene->m_Sg.recursive_search("Jupiter", MX::World::get().m_ActiveScene->m_Sg.m_Root);
  MX::search_holder->m_Trans.push_animation(MX::Y, 0.1f);
  MX::search_holder->m_Shader = MX::World::get().getShader("texture");
  MX::search_holder->m_Texture = MX::World::get().getTexture("2k_jupiter.jpg", 1);

  MX::World::get().m_ActiveScene->m_Sg.recursive_search("Saturn", MX::World::get().m_ActiveScene->m_Sg.m_Root);
  MX::search_holder->setLocalTransform(glm::scale(glm::fmat4(1.0f), glm::vec3(0.5, 0.5, 0.5)));
  MX::search_holder->setLocalTransform(glm::translate(glm::fmat4(1.0f), glm::vec3(3.0, 0.0, 0.0)));
  MX::search_holder->m_Shader = MX::World::get().getShader("texture");
  MX::search_holder->m_Texture = MX::World::get().getTexture("2k_saturn.jpg", 1);

  MX::World::get().m_ActiveScene->m_Sg.recursive_search("Rock", MX::World::get().m_ActiveScene->m_Sg.m_Root);
  MX::search_holder->m_Trans.push_translation(MX::FORWARDS, 5.0f);
  MX::search_holder->m_Shader = MX::World::get().getShader("texture");
  MX::search_holder->m_Texture = MX::World::get().getTexture("rock.jpg", 1);
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