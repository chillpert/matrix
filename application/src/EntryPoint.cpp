#include "matrix/Matrix.h"
#include <string>

MX::Camera* cam = &MX::Camera::get();
MX::Shader_OpenGL s1("trivial");
MX::Model m1("cube.obj");

void initialize() {
    
}

void update() {
    s1.use();
    glm::fmat4 view_matrix = cam->getViewMatrix();
    s1.setfMat4("view", view_matrix);
    glm::fmat4 projection_matrix = cam->getProjectionMatrix();
    s1.setfMat4("projection", projection_matrix);
}

void render() {
    s1.use();
    glm::fmat4 model_matrix = glm::fmat4(1.0f);
    s1.setfMat4("model", model_matrix);
    m1.setVertexAttributes();
    m1.draw();
}

int main() {
    // application testing
    MX::Application* app = &MX::Application::get();

    app->initialize(initialize);
    app->getWindow()->setTitle("My Application");

    // shader testing
    s1.create();
    s1.use();
    
    // model testing
    m1.setGeometry(GL_TRIANGLES); 

    // rendering loop
    while(app->isRunning()) {
        app->update(update);        
        app->render(render);
    }
    app->clean();

    // layer testing
    MX::Layer l1("l1");
    MX::Layer l2("l2");
    MX::Layer l3("l3");
    MX::Layer l4("l4");
    app->getLayerStack()->push(&l1);
    app->getLayerStack()->push(&l2);
    app->getLayerStack()->push(&l3);
    app->getLayerStack()->push(&l4);

    MX_INFO(std::to_string(app->getLayerStack()->getSize()));
    MX_INFO(app->getLayerStack()->toString());
    app->getLayerStack()->pop(&l2);

    MX_INFO(std::to_string(app->getLayerStack()->getSize()));
    MX_INFO(app->getLayerStack()->toString());

    return 0;
}