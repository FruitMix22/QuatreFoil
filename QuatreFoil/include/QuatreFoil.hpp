#pragma once
#include "Core/include/Layer.hpp"
#include "Buffers/include/VAO.hpp"
#include "Buffers/include/VBO.hpp"
#include "Buffers/include/FBO.hpp"
#include "Renderer/include/Renderer.hpp"
#include "Renderer/include/Shader.hpp"
#include "Renderer/include/Texture.hpp"
#include "Renderer/include/Camera.hpp"
#include "Renderer/include/Quad.hpp"
#include "Components/Renderable.hpp"
#include <entt/entt.hpp>
#include <vector>
#include <glm.hpp>

class QuatreFoil : public Layer
{
private:
	entt::registry m_registry;
	Renderer m_renderer;
	glm::vec4 triangleColour = { 1.f,1.f,1.f,1.f };

	glm::vec2 m_xPosTriangle = glm::vec2(200.f, 0.f);
	glm::vec2 cameraPos = glm::vec2(0.f, 0.f);

	// Only ever want one camera
	// No support for multiple camera's right now
	std::unique_ptr<Camera> m_camera;

	std::vector<Quad> m_quads;

	std::unique_ptr<Framebuffer>m_fbo;

	bool firstDock = true;

public:
	QuatreFoil(); // Default constructor
	void OnAttach() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnImGuiRender() override;
	void OnRender() override;

	// Generate entities -> Test for now
	void generateEntities();

	void generateFloor();
};