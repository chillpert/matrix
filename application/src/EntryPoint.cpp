#include "matrix/Matrix.h"

#define MX_W_ACTION 
#define MX_A_ACTION
#define MX_S_ACTION
#define MX_D_ACTION
#define MX_C_ACTION
#define MX_SPACE_ACTION
#define MX_ESCAPE_ACTION    Application::get().stop();
#define MX_L_SHIFT_ACTION

void initialize() {
    
}

void render() {
    
}

void update() {
    
}

int main() {    
    Matrix::Application* app = &Matrix::Application::get();
    
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