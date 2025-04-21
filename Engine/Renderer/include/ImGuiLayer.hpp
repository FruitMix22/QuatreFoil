#pragma once

struct GLFWwindow;

// Handles ImGui creation and deletion.
class ImGuiLayer
{
public:
    // Creates context for ImGui via the window.
    // @param window: current window.
    void Init(GLFWwindow* window);
    //Destroys ImGui context.
    void Shutdown();

    // Establishes a new frame.
    void Begin();
    // Establishes the frame has ended.
    void End();



private:

    GLFWwindow* m_window = nullptr; // Window that ImGui attatches to.
};
