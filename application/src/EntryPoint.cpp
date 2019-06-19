#include <Matrix.h>

void load_debug_scene()
{
  using namespace MX;

  MX_SCENE->push("Jupiter", "sphere.obj", "Root");
  MX_SCENE->push("Saturn", "sphere.obj", "Jupiter");

  MX_SCENE->push("Rock", "rock.obj", "Root");

  std::shared_ptr<Node> jupiter = MX_SCENEGRAPH.search("Jupiter", MX_ROOT);
  jupiter->setTransform(Y, 0.3f, 1);
  jupiter->setShader(MX_GET_SHADER("blinn_phong"));
  jupiter->setTexture(MX_GET_TEXTURE("2k_jupiter.jpg"));

  std::shared_ptr<Node> saturn = MX_SCENEGRAPH.search("Saturn", MX_ROOT);
  saturn->setTransform(SCALE, 0.4f, 0);
  saturn->setTransform(Y, 0.8f, 1);
  saturn->setTransform(RIGHT, 5.0f, 0);
  saturn->setShader(MX_GET_SHADER("blinn_phong"));
  saturn->setTexture(MX_GET_TEXTURE("2k_saturn.jpg"));

  std::shared_ptr<Node> rock = MX_SCENEGRAPH.search("Rock", MX_ROOT);
  rock->setTransform(SCALE, 0.05f, 0);
  rock->setTransform(BACKWARDS, 35.0f, 0);
  rock->setTransform(LEFT, 0.5f, 0);
  rock->setTransform(Y, 0.8f, 1);
  rock->setTransform(X, 0.5f, 1);
  rock->setShader(MX_GET_SHADER("phong"));
  rock->setTexture(MX_GET_TEXTURE("rock.jpg"));
}

void initialize()
{
  using namespace MX;

  MX_WORLD.initialize();
  MX_WORLD.push(std::shared_ptr<Scene>(new Scene("debug")));

#ifdef MX_DEBUG
  //load_debug_scene();
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

  static MX_SHADER assimp_shader("assimp_blinn_phong", 1);
  static Assimp_Model nano_suit(MX_MODEL_PATH + std::string("nanosuit/nanosuit.obj"));

  assimp_shader.use();
  glm::mat4 projection = MX_CAMERA.getProjectionMatrix();
  glm::mat4 view = MX_CAMERA.getViewMatrix();
  assimp_shader.setfMat4("projection", projection);
  assimp_shader.setfMat4("view", view);
  assimp_shader.setfVec3("lightPosition", glm::fvec3(0.0f, 5.0f, 5.0f));
  assimp_shader.setfVec3("lightColor", glm::fvec3(1.0f, 1.0f, 1.0f));
  assimp_shader.setfVec3("viewPosition", MX_WORLD.m_ActiveScene->m_Cam.getPosition());    
  assimp_shader.setFloat("ambientStrength", 0.08f);

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
  assimp_shader.setfMat4("model", model);
  nano_suit.render(assimp_shader);
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