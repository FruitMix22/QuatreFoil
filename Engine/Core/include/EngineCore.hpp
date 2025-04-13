#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

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

    void setVertPath(std::filesystem::path path) { m_vertPath = path; }
    void setFragPath(std::filesystem::path path) { m_fragPath = path; }

    // quick simple read shader file
    //TODO: actually understand this and sort in future
    std::string ReadShaderFile(const std::filesystem::path& filepath)
    {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open shader file: " + filepath.string());
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        return buffer.str();
    }

private:
    /// @brief GLFW window pointer
    GLFWwindow* m_window = nullptr;

    /// @brief Handles inputs.
    /// 
    /// If user presses ESC, close game
    void processInput();

    /// @brief Vertices for triangle
    float m_triangleVerts[9] =
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    /// @brief Vert Shader path
    std::filesystem::path m_vertPath;

    /// @brief Frag Shader path
    std::filesystem::path m_fragPath;

    GLuint m_VAO;
    GLuint m_VBO;
    GLuint shaderProgram;
};