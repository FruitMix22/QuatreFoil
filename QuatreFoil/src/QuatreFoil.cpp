#include "../QuatreFoil/include/QuatreFoil.hpp"
#include <iostream>

void QuatreFoil::OnAttach()
{
	std::cout << "Attaching Game to Engine...\n";
	generateEntities();
}

void QuatreFoil::OnUpdate()
{
	auto view = m_registry.view<Renderable>();

	for (auto entity : view)
	{
		auto& renderable = view.get<Renderable>(entity);

		renderable.m_shader->SetUniform("colour", triangleColour);
	}
}

void QuatreFoil::OnRender()
{
	m_renderer.Render(m_registry);
}

void QuatreFoil::generateEntities()
{
	float triangleVerts[] =
	{
		0.5f,  0.5f,    // top right
		0.5f, -0.5f,    // bottom right
	   -0.5f, -0.5f,    // bottom left
	   -0.5f,  0.5f    // top left
	};

	float triangleVerts2[] =
	{
		0.5f,  1.f,    // top right
		1.f, 0.5f,    // bottom right
	    0.5f, 0.5f,    // bottom left
	};


	unsigned int triangleIndeces[] =
	{
		0,1,3,
		1,2,3
	};

	unsigned int triangle2Indeces[] =
	{
		0,1,2
	};

	entt::entity triangle = m_registry.create();
	std::shared_ptr<VAO> triangleVAO = std::make_shared<VAO>(triangleVerts,triangleIndeces);
	triangleVAO->AddVertexBuffer(0, 2, GL_FLOAT, false, sizeof(float) * 2, (void*)0);
	
	const char* vertexPath = "../QuatreFoil/Assets/Shaders/TriangleVert.glsl";
	const char* fragPath = "../QuatreFoil/Assets/Shaders/TriangleFrag.glsl";

	std::shared_ptr<Shader> triangleShader = std::make_shared<Shader>(vertexPath, fragPath);

	auto& renderComponent = m_registry.emplace<Renderable>(triangle);
	renderComponent.m_vao = triangleVAO;
	renderComponent.m_shader = triangleShader;

	entt::entity triangle2 = m_registry.create();
	std::shared_ptr<VAO> triangle2VAO = std::make_shared<VAO>(triangleVerts2, triangle2Indeces);
	triangle2VAO->AddVertexBuffer(0, 2, GL_FLOAT, false, sizeof(float) * 2, (void*)0);

	std::shared_ptr<Shader> triangle2Shader = std::make_shared<Shader>(vertexPath, fragPath);

	auto& renderComponent2 = m_registry.emplace<Renderable>(triangle2);
	renderComponent2.m_vao = triangle2VAO;
	renderComponent2.m_shader = triangle2Shader;

}

void QuatreFoil::OnImGuiRender()
{
	ImGui::Begin("Debug");
	// Edit a color stored as 4 floats
	ImGui::ColorEdit3("Color", &triangleColour.x);
	ImGui::End();
}

