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

	// VBO

	// Generate the VBO with buffer id 1
	glGenBuffers(1, &m_VBO);
	// Buffer object is an array buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	// Attach triangle vert data to the buffer
	
    //           Type of Buffer	    Size that array takes   Vert data     Data is set only once
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_triangleVerts), m_triangleVerts, GL_STATIC_DRAW);

	// TODO: When handling a moving object, change GL_STATIC_DRAW to something else so its placed in faster memory
	

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

}

void EngineCore::unloadEngine()
{
	if (m_window)
	{
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
		// input
		processInput();

		// Clear with colour
		glClearColor(0.1f, 0.9f, 0.3f, 1.0f);

		// Clear the colour bits, leave depth alone for now
		glClear(GL_COLOR_BUFFER_BIT);


		glUseProgram(shaderProgram);
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap Buffers
		glfwSwapBuffers(m_window);

		// Check for updates
		glfwPollEvents();
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