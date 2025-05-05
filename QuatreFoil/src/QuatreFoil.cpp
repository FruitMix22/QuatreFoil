#include "../QuatreFoil/include/QuatreFoil.hpp"
#include <iostream>

QuatreFoil::QuatreFoil()
{
	m_camera = std::make_unique<Camera>(m_registry);
	m_fbo = std::make_unique<Framebuffer>(800,600);
}

void QuatreFoil::OnAttach()
{
	std::cout << "Attaching Game to Engine...\n";
}

void QuatreFoil::OnStart()
{
	// Generate entities
	generateEntities();
	generateFloor();
}

void QuatreFoil::OnUpdate()
{
	auto view = m_registry.view<Renderable, Transform>();
	
	for (auto entity : view)
	{
		auto& renderable = view.get<Renderable>(entity);
		auto& transformable = view.get<Transform>(entity);

		renderable.m_shader->SetUniform("projection", m_camera->GetProjectionMatrix());
		renderable.m_shader->SetUniform("view", m_camera->GetViewMatrix());
		renderable.m_shader->SetUniform("colour", triangleColour);
		renderable.m_shader->SetUniform("model",transformable.GetModelMatrix());
	}

	auto& transform = m_registry.get<Transform>(m_quads[0].GetEntity());
	transform.position = glm::vec2(m_xPosTriangle.x, m_xPosTriangle.y);

}

void QuatreFoil::OnRender()
{
	m_fbo->Bind();
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	m_renderer.Render(m_registry);
	m_fbo->Unbind();
}

void QuatreFoil::generateEntities()
{
	//m_quads.emplace_back(m_registry);
	//m_quads.back().CreateQuad(glm::vec2(100,100), glm::vec2(200,200));
}

void QuatreFoil::generateFloor()
{
	// temp number of floors
	size_t totalTiles = 5;
	float xPositionTile	 = -110.f;
	//std::shared_ptr<Texture> grass = std::make_shared<Texture>("../QuatreFoil/Assets/Textures/grass.png");

	for (int i = 0; i < totalTiles; i++)
	{
		m_quads.emplace_back(m_registry);
		//m_quads.back().SetTexture(grass);
		m_quads.back().CreateQuad(glm::vec2(xPositionTile, -600),glm::vec2(110,100));
		xPositionTile += 200.f;
	}
}

void QuatreFoil::OnImGuiRender()
{ 
	ImGui::Begin("Debug");
	ImGui::Image(static_cast<intptr_t>(m_fbo->GetTextureID()), ImVec2(800, 600), ImVec2(0, 1), ImVec2(1, 0));
	ImGui::Text("Entity Colour");
	// Edit a color stored as 4 floats
	ImGui::ColorEdit3("Color", &triangleColour.x);
	ImGui::SliderFloat2("X/Y Pos", glm::value_ptr(m_xPosTriangle), -600.f, 800.f);
	ImGui::End();
}

