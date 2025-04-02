#include <glfw3.h>
#include <iostream>

int main()
{
    if (!glfwInit()) 
    {
        std::cerr << "It worked" << std::endl;
        return -1;
    }
    std::cout << "You blew it up somehow" << std::endl;

    glfwTerminate();

    return 0;
}