#include "Core/include/EngineCore.hpp"

EngineCore::EngineCore(const std::string& windowTitle)
{
	m_window = nullptr;
	if (!loadEngine(windowTitle))
	{
		unloadEngine();
	}
}

bool EngineCore::loadEngine(const std::string& windowTitle)
{
	// Initialise all GLFW functions
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << " GLFW failed to initialise!\n";
		unloadEngine();
		return false;
	}

	// Set versions and necessary stuff for glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	m_window = glfwCreateWindow(1920, 1080, windowTitle.c_str(), NULL, NULL);
	if (m_window == NULL)
	{
		std::cout << "Failed to create GLFW window!\n";
		unloadEngine();
		return false;
	}

	/// Set the window as the current context
	glfwMakeContextCurrent(m_window);

	// Load all OpenGL stuff
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		unloadEngine();
		return false;
	}

	// Set clear colour
	glClearColor(m_clearColour[0], m_clearColour[1], m_clearColour[2], m_clearColour[3]);

	// Load ImGui if debugging is active.
	if (m_isDebugMenu)
	{
		m_imGui.Init(m_window);
	}

	if (!Input::Init(m_window))
	{
		std::cerr << "Failed to initialise Inputs in Engine Core." << std::endl;
		std::cerr << "WARNING: Inputs will not work." << std::endl;
		return false;
	}

	return true;
}

void EngineCore::unloadEngine()
{
	if (m_window)
	{
		if (m_isDebugMenu)
		{
			// Can only shutdown while window exists and if debugging is active
			m_imGui.Shutdown();
		}

		std::cout << "\nTerminating window...\n";
		m_window = nullptr;
	}
	// Terminate all GLFW processes
	glfwTerminate();
	std::cout << "Shutdown.\n";
}

int EngineCore::runEngine()

{
	if (m_layer) { m_layer->OnStart(); }
	// Start render loop.
	while (!glfwWindowShouldClose(m_window))
	{
		// Calculate frame time
		float currentFrameTime = static_cast<float>(glfwGetTime());
		dt = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		if (m_layer) { m_layer->m_dt = this->dt; }

		if (m_layer->m_terminate) { glfwSetWindowShouldClose(m_window, true); }
		// Check for updates
		glfwPollEvents();
		// Start ImGui frame
		m_imGui.Begin();

		glClearColor(1.f, 1.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Run code from the Game Layer.
		if (m_layer) { m_layer->OnUpdate(); }
		Input::ProcessInput();
		if (m_layer) { m_layer->OnImGuiRender(); }
		if (m_layer) { m_layer->OnRender(); }

		// End ImGui frame
		m_imGui.End();

		// Swap Buffers
		glfwSwapBuffers(m_window);

		// Check for updates
		glfwPollEvents();
	}
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
