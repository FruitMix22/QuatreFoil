#include "Core/include/EngineCore.hpp"

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

	m_imGui.Init(m_window);



	// Create a shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// same thing
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertShaderStr = ReadShaderFile(m_vertPath);
	std::string fragShaderStr = ReadShaderFile(m_fragPath);

	const char* vertShaderSrc = vertShaderStr.c_str();
	const char* fragShaderSrc = fragShaderStr.c_str();

	glShaderSource(vertexShader, 1, &vertShaderSrc, NULL);
	glShaderSource(fragmentShader, 1, &fragShaderSrc, NULL);

	// Compile Shader
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	int success;
	char infoLog[512];

	// For Vertex Shader
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Vertex Shader Compilation Failed:\n" << infoLog << std::endl;
	}

	// For Fragment Shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Fragment Shader Compilation Failed:\n" << infoLog << std::endl;
	}
	

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	}



	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// VBO

	// Generate the VBO with buffer id 1
	glGenBuffers(1, &m_VBO);
	// Buffer object is an array buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glGenVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_triangleVerts), m_triangleVerts, GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glUseProgram(shaderProgram);
	glBindVertexArray(m_VAO);

	// TODO : BUFFER CLASSES!!!!!!!

}

void EngineCore::unloadEngine()
{
	if (m_window)
	{
		// Can only shutdown while window exists
		m_imGui.Shutdown();
		// Terminate all GLFW processes
		glfwDestroyWindow(m_window);
		m_window = nullptr;
	}
	glfwTerminate();
	
}

int EngineCore::runEngine()

{
	// render loop
	while (!glfwWindowShouldClose(m_window))
	{
		// Check for updates
		glfwPollEvents();
		// input
		processInput();
		// Clear the colour bits, leave depth alone for now
		glClear(GL_COLOR_BUFFER_BIT);
		// Clear with colour
		glClearColor(0.1f, 0.9f, 0.3f, 1.0f);

		// Begin ImGui
		m_imGui.Begin();

		// UI panels go here
		ImGui::Begin("Debug Panel");
		ImGui::SliderFloat("Value", &m_RandomVert, -1.0f, 1.0f);
		ImGui::End();

		float m_triangleVerts[9] =
		{
			m_RandomVert, m_RandomVert, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		glGenVertexArrays(1, &m_VAO);

		glBindVertexArray(m_VAO);
		// 2. copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_triangleVerts), m_triangleVerts, GL_STATIC_DRAW);
		// 3. then set our vertex attributes pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glUseProgram(shaderProgram);
		glBindVertexArray(m_VAO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(m_triangleVerts), m_triangleVerts, GL_DYNAMIC_DRAW);
		glUseProgram(shaderProgram);
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		std::cout << m_RandomVert;

		// End ImGui
		m_imGui.End();

		// Swap Buffers
		glfwSwapBuffers(m_window);


	}
	// End the window
	unloadEngine();
	return 0;
}

void EngineCore::processInput()
{
	// If user presses escape, set window close to true
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);
}