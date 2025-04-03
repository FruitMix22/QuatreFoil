#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Game Dev Project", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL();

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}