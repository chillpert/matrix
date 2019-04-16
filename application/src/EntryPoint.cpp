#include "matrix/Matrix.h"
#include <string>

MX::Camera* cam = &MX::Camera::get();
MX::Shader_OpenGL s1("trivial");

void initialize() {
    
}

void update() {
    s1.use();
    // set view
    glm::fmat4 view_matrix = cam->getViewMatrix();
    s1.setfMat4("view", view_matrix);
    // set projection
    glm::fmat4 projection_matrix = cam->getProjectionMatrix();
    s1.setfMat4("projection", projection_matrix);
}

void render() {
    s1.use();
    glm::fmat4 model_matrix = glm::fmat4(1.0f);
    s1.setfMat4("model", model_matrix);
    // draw vertices
}

int main() {
    // application testing
    MX::Application* app = &MX::Application::get();

    app->initialize(initialize);
    app->getWindow()->setTitle("My Application");

    // shader testing
    s1.create();
    s1.use();

    // rendering loop
    while(app->isRunning()) {
        app->update(update);        
        app->render(render);
    }
    app->clean();

    // parse testing
    MX::Model_OpenGL model_opengl("cube.obj");
    model_opengl.parse();

    return 0;
}