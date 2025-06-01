#include "../ExampleGame/include/ExampleGame.hpp"
#include <iostream>

ExampleGame::ExampleGame()
{
	// Make a camera object & framebuffer
	m_camera = std::make_unique<Camera>(m_registry);
	m_fbo = std::make_unique<Framebuffer>(1920, 1080, 0);
	m_fbo->Bind(); 
}

void ExampleGame::OnAttach()
{
	std::cout << "Attaching Game to Engine...\n";
}

void ExampleGame::OnStart()
{
	m_camera->Setposition(glm::vec2(0.f, 0.f)); // Set camera position

	GenerateTriangle();
}

void ExampleGame::OnUpdate()
{
	// Update all uniforms for all renderables
	auto& view = m_registry.view<Renderable, Transform>();
	for (auto entity : view)
	{
		auto& renderable = view.get<Renderable>(entity);
		auto& transformable = view.get<Transform>(entity);

		renderable.m_shader->SetUniform("projection", m_camera->GetProjectionMatrix());
		renderable.m_shader->SetUniform("view", m_camera->GetViewMatrix());
		renderable.m_shader->SetUniform("model", transformable.GetModelMatrix());
	}
} 

void ExampleGame::OnRender()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0,0,1920,1080); 
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f); // or any background color
	glClear(GL_COLOR_BUFFER_BIT);
	m_renderer.Render(m_registry); 	// Run the renderer
}

void ExampleGame::OnImGuiRender()
{
	ImGui::Begin("Example Game Layer");
	ImGui::Text("FPS: %.1f", GetFPS());
	ImGui::Text("Camera Position: (%.2f, %.2f)", m_camera->GetPosition().x, m_camera->GetPosition().y);
	auto& view = m_registry.view<Transform>();
	for (auto& entity : view)
	{
		auto& transformComp = m_registry.get<Transform>(entity);
		ImGui::SliderFloat2("Position x", &transformComp.position.x,  -600.f, 21.f);

	}
	ImGui::End();
}

float ExampleGame::GetFPS()
{
	fpsTimeAccumulate += m_dt;
	if (fpsTimeAccumulate >= 1.0f)
	{
		// Change FPS and reset timer
		m_fps = 1.0f / m_dt;
		fpsTimeAccumulate = 0.0f;
	}
	return m_fps;
}

void ExampleGame::GenerateTriangle()
{
	float triangleVerts[] = 
	{
		0.5f,  0.5f,    // top right
		0.5f, -0.5f,    // bottom right
	   -0.5f, -0.5f,    // bottom left
	   -0.5f,  0.5f    // top left
	};


	unsigned int triangleIndeces[] =
	{
		0,1,3,
		1,2,3
	};

	entt::entity triangle = m_registry.create();
	std::shared_ptr<VAO> triangleVAO = std::make_shared<VAO>(triangleVerts, triangleIndeces);
	triangleVAO->AddVertexBuffer(0, 2, GL_FLOAT, false, sizeof(float) * 2, (void*)0);

	const char* vertexPath = "../ExampleGame/Assets/Shaders/TriangleVert.glsl";
	const char* fragPath = "../ExampleGame/Assets/Shaders/TriangleFrag.glsl";

	std::shared_ptr<Shader> triangleShader = std::make_shared<Shader>(vertexPath, fragPath);

	auto& renderComponent = m_registry.emplace<Renderable>(triangle);
	renderComponent.m_vao = triangleVAO;
	renderComponent.m_shader = triangleShader;

	m_registry.emplace<RenderLayer>(triangle, RenderLayer::UI);
	auto& transformComp = m_registry.emplace<Transform>(triangle);
	transformComp.position = glm::vec2(-200.f, -200.f);
	transformComp.scale = glm::vec2(100.f, 100.f);

}





