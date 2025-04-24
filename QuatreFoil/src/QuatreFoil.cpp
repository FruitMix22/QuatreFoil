#include "../QuatreFoil/include/QuatreFoil.hpp"
#include <iostream>

void QuatreFoil::OnAttach()
{
	std::cout << "Attaching Game to Engine...\n";
	generateEntities();
}

void QuatreFoil::OnUpdate()
{
	// Get the Camera
	auto firstCamera = m_registry.view<Camera>();
	glm::mat4 cameraView;
	glm::mat4 projection;

	if (!firstCamera.empty())
	{
		auto entity = *firstCamera.begin();
		auto& camera = firstCamera.get<Camera>(entity);

		cameraView = camera.GetViewMatrix();
		projection = camera.GetProjectionMatrix();
		camera.position = cameraPos;
	}

	auto view = m_registry.view<Renderable, Transform>();
	
	for (auto entity : view)
	{
		auto& renderable = view.get<Renderable>(entity);
		auto& transformable = view.get<Transform>(entity);

		transformable.position = glm::vec2(m_xPosTriangle.x, m_xPosTriangle.y);


		renderable.m_shader->SetUniform("projection", projection);
		renderable.m_shader->SetUniform("view", cameraView);
		renderable.m_shader->SetUniform("colour", triangleColour);
		renderable.m_shader->SetUniform("model",transformable.GetModelMatrix());
	}


}

void QuatreFoil::OnRender()
{
	m_renderer.Render(m_registry);
}

void QuatreFoil::generateEntities()
{
	// Camera
	entt::entity camera = m_registry.create();
	m_registry.emplace<Camera>(camera);


	float triangleVerts[] =
	{	// x   //y   //u   //v
		-1.f, -1.f, 0.f, 0.f, // bottom-left
		1.0f, -1.f, 1.0f, 0.f, // bottom-right
		1.0f, 1.0f, 1.0f, 1.0f, // top-right
		-1.f, 1.0f, 0.f, 1.0f  // top-left
	};

	unsigned int triangleIndeces[] =
	{
		0,1,3,
		1,2,3
	};

	entt::entity triangle = m_registry.create();
	std::shared_ptr<VAO> triangleVAO = std::make_shared<VAO>(triangleVerts,triangleIndeces);
	triangleVAO->AddVertexBuffer(0, 2, GL_FLOAT, false, sizeof(float) * 4, (void*)0);
	triangleVAO->AddVertexBuffer(1, 2, GL_FLOAT, false, sizeof(float) * 4, (void*)(2 * sizeof(float)));
	
	const char* vertexPath = "../QuatreFoil/Assets/Shaders/TriangleVert.glsl";
	const char* fragPath = "../QuatreFoil/Assets/Shaders/TriangleFrag.glsl";

	const char* imagePath = "../QuatreFoil/Assets/Textures/container.jpg";

	std::shared_ptr<Texture> triangleTexture = std::make_shared<Texture>(imagePath);

	std::shared_ptr<Shader> triangleShader = std::make_shared<Shader>(vertexPath, fragPath);

	auto& renderComp = m_registry.emplace<Renderable>(triangle);
	renderComp.m_vao = triangleVAO;
	renderComp.m_shader = triangleShader;
	renderComp.m_texture = triangleTexture;
	
	auto& transformComp = m_registry.emplace<Transform>(triangle);
	transformComp.position = glm::vec2(100,100);
	transformComp.scale = glm::vec2(200,200);
}

void QuatreFoil::OnImGuiRender()
{
	ImGui::Begin("Debug");
	ImGui::Text("Entity Colour");
	// Edit a color stored as 4 floats
	ImGui::ColorEdit3("Color", &triangleColour.x);
	ImGui::Text("Quad X Pos");
	ImGui::SliderFloat2("X Pos", glm::value_ptr(m_xPosTriangle), -600.f, 800.f);
	ImGui::Text("Camera Pos");
	ImGui::SliderFloat2("Camera", glm::value_ptr(cameraPos), -500.f, 500.f);
	ImGui::End();
}

