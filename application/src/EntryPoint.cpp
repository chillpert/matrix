#include "matrix/Matrix.h"
#include <string>

void initialize() {
    
}

void update() {
    
}

int main() {    
    MX::Application* app = &MX::Application::get();

    app->initialize(initialize);
    
    app->getWindow()->setTitle("My Application");
    // rendering loop
    while(app->isRunning()) {
        app->update(update);        
        app->render();
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