#include "Core/include/EngineCore.hpp"

EngineCore::EngineCore(const std::string& windowTitle)
{
	m_window = nullptr;
	void framebuffer_size_callback(GLFWwindow * window, int width, int height);
	void processInput(GLFWwindow * window);
	loadEngine(windowTitle);
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

	if (m_isDebugMenu)
	{
		m_imGui.Init(m_window);
	}
}

// FIGURE OUT WHY ITS RUNNING THE OUTSIDE IF TWICE
void EngineCore::unloadEngine()
{
	if (m_window)
	{
		if (m_isDebugMenu)
		{
			// Can only shutdown while window exists
			m_imGui.Shutdown();
		}

		// Terminate all GLFW processes
		std::cout << "\nTerminating window...\n";
		m_window = nullptr;
	}
	glfwTerminate();
	std::cout << "Shutdown.\n";
}

int EngineCore::runEngine()

{
	// render loop
	while (!glfwWindowShouldClose(m_window))
	{
		// Check for updates
		glfwPollEvents();

		if (m_layer) { m_layer->OnUpdate(); }

		// Begin ImGui
		m_imGui.Begin();
		if(m_layer) { m_layer->OnImGuiRender(); }
		

		// Clear the colour bits, leave depth alone for now
		glClear(GL_COLOR_BUFFER_BIT);
		// Clear with colour
		glClearColor(m_clearColour[0], m_clearColour[1], m_clearColour[2], m_clearColour[3]);

		// Render loop
		if (m_layer) { m_layer->OnRender(); }


		m_imGui.End();

		// Swap Buffers
		glfwSwapBuffers(m_window);
	}
	// End the window
	unloadEngine();
	return 0;
}

void EngineCore::SetLayer(std::shared_ptr<Layer> layer)
{
	m_layer = layer;
	if (m_layer)
	{
		m_layer->OnAttach();
		std::cout << "Succesful!\n";
	}
}
