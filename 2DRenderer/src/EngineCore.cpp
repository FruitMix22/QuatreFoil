#include "EngineCore.hpp"

EngineCore::EngineCore()
{
	m_window = nullptr;
	void framebuffer_size_callback(GLFWwindow * window, int width, int height);
	void processInput(GLFWwindow * window);
}


bool EngineCore::loadEngine(const std::string& windowTitle)
{
	// Initialise all GLFW functions
	if (glfwInit() == GLFW_FALSE)
	{
		// Return false if fails
		std::cout << " GLFW failed to initialise!\n";
		unloadEngine();
		return false;
	}

	// Set versions and necessary stuff for glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	m_window = glfwCreateWindow(800, 600, windowTitle.c_str(), NULL, NULL);
	if (m_window == NULL)
	{
		// Return false if fails
		std::cout << "Failed to create GLFW window!\n";
		unloadEngine();
		return false; 
	}

	/// Set the window as the current context
	glfwMakeContextCurrent(m_window);

	// Load all OpenGL stuff
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		// If fails, close all
		std::cout << "Failed to initialize GLAD" << std::endl;
		unloadEngine();
		return -1;
	}
}

void EngineCore::unloadEngine()
{
	if (m_window)
	{
		// Terminate all GLFW processes
		glfwDestroyWindow(m_window);
		m_window = nullptr;
	}
	// TODO: bro i moved this out because even if m_window is null, you gotta glfwTerminate();
	glfwTerminate();
}

int EngineCore::runEngine()

{
	// render loop
	while (!glfwWindowShouldClose(m_window))
	{
		// input
		processInput();

		// Swap Buffers
		glfwSwapBuffers(m_window);

		// Check for updates
		glfwPollEvents();
		
		// Clear with colour
		glClearColor(0.1f, 0.9f, 0.3f, 1.0f);

		// Clear the colour bits, leave depth alone for now
		glClear(GL_COLOR_BUFFER_BIT);
	}
	// End the window
	unloadEngine();
	return 0;
}

// Process input
void EngineCore::processInput()
{
	// If user presses escape, set window close to true
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);
}