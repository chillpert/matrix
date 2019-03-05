#include "matrix/Matrix.h"

void initialize() {
    
}

void render() {
    
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
        app->render(render);
    }
    app->clean();

    return 0;
}