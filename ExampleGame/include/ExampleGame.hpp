#pragma once
#include "imgui_internal.h"
#include "imgui.h"
#include "Core/include/Layer.hpp"
#include "Buffers/include/VAO.hpp"
#include "Buffers/include/VBO.hpp"
#include "Buffers/include/FBO.hpp"
#include "Renderer/include/Renderer.hpp"
#include "Renderer/include/Shader.hpp"
#include "Renderer/include/Texture.hpp"
#include "Renderer/include/Camera.hpp"
#include "Components/Renderable.hpp"
#include "Components/RenderLayer.hpp"
#include "Components/Animator.hpp"
#include "Components/Transform.hpp"
#include "Core/include/Input.hpp"
#include "Core/include/Console.hpp"
#include <entt/entt.hpp>
#include <vector>
#include <glm.hpp>

// Game layer.
class ExampleGame : public Layer
{
public:
	// Parent functions.
	ExampleGame();
	void OnAttach() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnImGuiRender() override;
	void OnRender() override;

	// Updates m_FPS every second.
	// @returns Current FPS.
	float GetFPS();

	void GenerateTriangle();

private:
	entt::registry m_registry; // Entity registry.
	Renderer m_renderer; // Renderer object.
	std::unique_ptr<Framebuffer>m_fbo; // Frame buffer. 

	std::unique_ptr<Camera> m_camera; // Camera object.
	glm::vec2 cameraPos = glm::vec2(0.f, 0.f); // Position of camera (world space). 

	float fpsTimeAccumulate = 0.0f; // Seconds since last frame update
	float m_fps = 0.0f; // FPS

};