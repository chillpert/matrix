#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Matrix {

    class MATRIX_API Application {
    public:
        ~Application();
        static Application &get();
        void start(void (*initialize_func)(), void (*update_func)(), void (*render_func)());
        void setWidth(int width);
        void setHeight(int height);
        void setTitle(std::string title);
        void stop();
    private: 
        Application();
        void initialize(void (*initialize_func)());
        void render(void (*render_func)());
        void update(void (*update_func)());
        void clean();

        GLFWwindow* m_Window;
        int m_Width;
        int m_Height;
        bool m_Running;
        std::string m_Title;
    };  

    MATRIX_API void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    MATRIX_API void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    MATRIX_API void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    MATRIX_API void processInput(GLFWwindow *window);
}

#endif // APPLICATION_H