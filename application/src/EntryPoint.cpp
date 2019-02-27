#include "matrix/Matrix.h"

void initialize() {
    
}

void render() {
    
}

void update() {
    
}

int main() {    
    Matrix::Application* app = &Matrix::Application::get();
    
    app->initialize(initialize);
    // rendering loop
    while(app->isRunning()) {
        app->update(update);
        app->render(render);
    }
    app->clean();

    return 0;
}