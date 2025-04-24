#pragma once
#include "Core/include/Layer.hpp"
#include <entt/entt.hpp>
#include "Buffers/include/VAO.hpp"
#include "Buffers/include/VBO.hpp"
#include "Renderer/include/Renderer.hpp"
#include "Renderer/include/Shader.hpp"
#include "Renderer/include/Texture.hpp"
#include "Components/Renderable.hpp"
#include "Components/Camera.hpp"
#include "Components/Transform.hpp"
#include <glm.hpp>

class QuatreFoil : public Layer
{
private:
	entt::registry m_registry;
	Renderer m_renderer;
	glm::vec4 triangleColour = { 1.f,1.f,1.f,1.f };

	glm::vec2 m_xPosTriangle = glm::vec2(200.f, 0.f);
	glm::vec2 cameraPos = glm::vec2(0.f, 0.f);
public:
	QuatreFoil() {}; // Default constructor
	void OnAttach() override;
	void OnUpdate() override;
	void OnImGuiRender() override;
	void OnRender() override;

	void generateEntities();
};