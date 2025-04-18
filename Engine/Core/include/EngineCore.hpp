#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <imgui.h>
#include "Renderer/include/ImGuiLayer.hpp"
#include "Renderer/include/Renderer.hpp"
#include "Core/include/Layer.hpp"

/// <summary>
/// 
/// Handles the basics of the engine.
/// Runs functions and creates ' game loop '
/// 
/// </summary>

class EngineCore
{

public:
    /// @brief Initialises class values
    /// @param windowTitle: Title of the window
    EngineCore(const std::string& windowTitle);

    /// @brief Runs unloadEngine automatically
    ~EngineCore() { unloadEngine(); }
     
    /// @brief Loads the Engine.
    /// 
    /// Sets up GLFW, necessary before anything is done
    /// @param windowTitle: Title of the window
    /// @return TRUE if passes, or FALSE if it fails
    bool loadEngine(const std::string& title);

    /// @brief Unloads the engine.
    /// 
    /// Terminates window and forces nullptr
    void unloadEngine();

    /// @brief Main core game loop
    /// 
    /// Processes input and swaps GLFW buffers and
    /// clears screen with colour (FOR NOW)
    /// @return 0 when game is no longer in loop
    int runEngine();

    /// Sets layer from the users game
    void SetLayer(std::shared_ptr<Layer> layer);

    /// Is ImGui going to be used?
    bool m_isDebugMenu = true;

    /// Clear colour
    float m_clearColour[4] = { 1.0f,1.0f,0.0f, 1.0f };
private:
    /// GLFW window pointer
    GLFWwindow* m_window = nullptr;
    /// ImGui
    ImGuiLayer m_imGui;
    /// Empty layer
    std::shared_ptr<Layer> m_layer = nullptr;
};