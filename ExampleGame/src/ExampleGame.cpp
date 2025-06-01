#include "../ExampleGame/include/ExampleGame.hpp"
#include <iostream>

// This file shows an example scene of rendering a basic rectangle, to see an example of a game with this,
// check the repository again and look in the GameRelease branch.

// This sets up a frame buffer, a camera, and a rectangle entity.

// To render anything at mimimum, you will need -
/*
- A registry to hold entities and its components.
- An entity with a renderable component that includes:
	- A VAO object with vertex data attatched to the renderable comp.
	- A shader object with vertex and fragment shaders.
	- And to add a vertex buffer for the shaders to retrieve
	  the vertex data from the VAO.
- Run the renderer ( renders anything with renderable component)
*/


// For example case, this example uses more features,
/*
- It uses a camera object to use 'world space'.
- It uses a frame buffer, which can be used to bind the other buffers.
- It also adds uniforms for the camera and rectangle colour
  to the shader, so that the rectangle can be rendered in the correct position and colour.
- It also uses ImGui as an example to show how it can be used.
*/

ExampleGame::ExampleGame()
{
	// Defines a camera and FBO.

    // Camera is an entity so it needs registry reference.
	m_camera = std::make_unique<Camera>(m_registry);
	// FBO is setup by passing through width, height and buffer id (currently 0 to render to screen).
	m_fbo = std::make_unique<Framebuffer>(1920, 1080, 0);
}

void ExampleGame::OnAttach()
{
	// This isnt neccesary, but shows in the console what is happening.
	std::cout << "Attaching Game to Engine...\n";
}

void ExampleGame::OnStart()
{
	// Set camera position to world centre.
	m_camera->Setposition(glm::vec2(0.f, 0.f)); // Set camera position

	// Generate a rectangle entity.
	GenerateRectangle();

	// Register inputs that run rectangle movement functions.
	Input::RegisterCallBack(GLFW_KEY_A, [this] {MoveSquareWithA(m_dt);});
	Input::RegisterCallBack(GLFW_KEY_D, [this] {MoveSquareWithD(m_dt);});
}

void ExampleGame::OnUpdate()
{
	// Update all uniforms for all renderables

	// Get all entities with Renderable and Transform components.
	auto& view = m_registry.view<Renderable, Transform>();
	for (auto entity : view)
	{
		// Get components.
		auto& renderable = view.get<Renderable>(entity);
		auto& transformable = view.get<Transform>(entity);

		// Set camera uniforms, and colour of rectangle.
		renderable.m_shader->SetUniform("projection", m_camera->GetProjectionMatrix());
		renderable.m_shader->SetUniform("view", m_camera->GetViewMatrix());
		renderable.m_shader->SetUniform("model", transformable.GetModelMatrix());
		renderable.m_shader->SetUniform("colour", m_rectangleColour);
	}
} 

void ExampleGame::OnRender()
{
	// Clear last colour.
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f); 
	// Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT);
	// Run the renderer.
	// This will render all entities with a Renderable component.
	m_renderer.Render(m_registry); 	
}

void ExampleGame::OnImGuiRender()
{
	// Sets the next window to be large enough for all components.
	ImGui::SetNextWindowSize(ImVec2(400, 150), ImGuiCond_FirstUseEver);


	ImGui::Begin("Example Game Layer");	// Begins new window
	ImGui::Text("FPS: %.1f", GetFPS()); // Display FPS
	ImGui::ColorEdit3("Rectangle Colour", (float*)&m_rectangleColour); // Edit rectangle colour
	ImGui::SliderFloat("Camera pos.x ", &cameraPos.x, -500, 500); // Edit camera position
	m_camera->Setposition(cameraPos); // Update camera position
	auto& view = m_registry.view<Transform>();
	for (auto& entity : view)
	{
		// For every entity with a transform component (only rectangle in this case),
		// display position and edit it.
		auto& transformComp = m_registry.get<Transform>(entity);
		ImGui::SliderFloat2("Rectangle Position", &transformComp.position.x,  -600.f, 21.f);

	}
	ImGui::End(); // End the ImGui instance
}

float ExampleGame::GetFPS()
{
	// Calculate fps based on time between frames, and update evry so often.
	// Only updates every second as its easier to read rather than
	// changing every frame.
	fpsTimeAccumulate += m_dt;
	if (fpsTimeAccumulate >= 1.0f)
	{
		// Change FPS and reset timer
		m_fps = 1.0f / m_dt;
		fpsTimeAccumulate = 0.0f;
	}
	return m_fps;
}

void ExampleGame::GenerateRectangle()
{
	// Vertices of the rectangle.
	float rectangleVerts[] = 
	{
		0.5f,  0.5f,    // top right
		0.5f, -0.5f,    // bottom right
	   -0.5f, -0.5f,    // bottom left
	   -0.5f,  0.5f    // top left
	};

	// Indices of the rectangle.
	unsigned int rectangleIndeces[] =
	{
		0,1,3,
		1,2,3
	};

	// Create an entity -> the rectangle and add it to the entity registry.
	entt::entity rectangle = m_registry.create();

	// Create a VAO (which automatically makes a VBO and EBO to optimise).
	std::shared_ptr<VAO> rectangleVAO = std::make_shared<VAO>(rectangleVerts, rectangleIndeces);
	// Add the vertex data so the vertex shader can retrieve it.
	rectangleVAO->AddVertexBuffer(0, 2, GL_FLOAT, false, sizeof(float) * 2, (void*)0);

	// Paths for the shaders.
	const char* vertexPath = "../ExampleGame/Assets/Shaders/triangleVert.glsl";
	const char* fragPath = "../ExampleGame/Assets/Shaders/triangleFrag.glsl";

	// Create a shader object with the vertex and fragment shader paths.
	std::shared_ptr<Shader> rectangleShader = std::make_shared<Shader>(vertexPath, fragPath);

	// Attatch the VAO and shader to the Renderable component of the rectangle entity.
	auto& renderComponent = m_registry.emplace<Renderable>(rectangle);
	renderComponent.m_vao = rectangleVAO;
	renderComponent.m_shader = rectangleShader;

	// Set the render layer to be front.
	m_registry.emplace<RenderLayer>(rectangle, RenderLayer::UI);

	// Create a Transform component for the rectangle entity and set
	// its position and scale.
	auto& transformComp = m_registry.emplace<Transform>(rectangle);
	transformComp.position = glm::vec2(-200.f, -200.f);
	transformComp.scale = glm::vec2(100.f, 100.f);

}

void ExampleGame::MoveSquareWithA(float dt)
{
	auto& view = m_registry.view<Transform>();
	for (auto& entity : view)
	{	// for every entity with a transform (currently on the rectangle), move the rectangle to the left.
		auto& transformComp = m_registry.get<Transform>(entity);
		transformComp.position.x -= 100.f * dt; 
	}
}

void ExampleGame::MoveSquareWithD(float dt)
{
	auto& view = m_registry.view<Transform>();
	for (auto& entity : view)
	{
		// for every entity with a transform (currently on the rectangle), move the rectangle to the left.
		auto& transformComp = m_registry.get<Transform>(entity);
		transformComp.position.x += 100.f * dt; 
	}
}





