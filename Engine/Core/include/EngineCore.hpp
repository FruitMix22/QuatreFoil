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

// Handles the basics of the engine.
// Runs functions and creates game loop.
class EngineCore
{

public:
    // Initialises class values.
    // @param windowTitle: Title of the window.
    EngineCore(const std::string& windowTitle);

    // Deallocates memory
    ~EngineCore() { unloadEngine(); }
     
    // Loads the Engine and sets up GLFW window.
    // @param title: Title of the window.
    // @return TRUE if passes, or FALSE if it fails.
    bool loadEngine(const std::string& title);

    // Unloads the engine.
    // Terminates window and forces nullptr.
    // Is automatically ran in destruct.
    void unloadEngine();

    // Runs the core game loop.
    // @return 0 when game is no longer in loop.
    int runEngine();

    // Sets layer from the users game.
    // @param layer: Your game layer.
    void SetLayer(std::shared_ptr<Layer> layer);

    // Sets debug mode.
    // @param status: True/False for wether debug mode is on.
    void SetImGUI(bool status) { m_isDebugMenu = status; }
  
private:
    GLFWwindow* m_window = nullptr; // GLFW window pointer
    ImGuiLayer m_imGui; // Manages ImGui UI
    std::shared_ptr<Layer> m_layer = nullptr; // Active game layer
    bool m_isDebugMenu = true;  // should ImGui be active? 
    float m_clearColour[4] = { 1.0f,1.0f,1.0f, 1.0f };  // glClear colour
};