#pragma once

class ImGuiLayer
{
public:
    void Init(GLFWwindow* window);
    void Begin();
    void End();
    void Shutdown();
private:
    GLFWwindow* m_window = nullptr;
};
