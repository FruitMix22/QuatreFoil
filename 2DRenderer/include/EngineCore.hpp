#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

class EngineCore
{
public:
    /// @brief Initialises class values
    EngineCore();

    /// @brief Runs unloadEngine automatically
    ~EngineCore() { unloadEngine(); }
      
    /// @brief Loads the Engine.
    /// 
    /// Sets up GLFW, necessary before anything is done
    /// @param title Title of the window
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
    /// 
    /// @warning MUST RUN loadEngine() before!
    /// @return 0 when game is no longer in loop
    int runEngine();



private:
    /// @brief GLFW window pointer
    GLFWwindow* m_window;

    /// @brief Handles inputs.
    /// 
    /// If user presses ESC, close game
    void processInput();
};