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
#include "Renderer/include/Quad.hpp"
#include "Components/Renderable.hpp"
#include "Components/Player.hpp"
#include "Core/include/Input.hpp"
#include <entt/entt.hpp>
#include <vector>
#include <glm.hpp>

// Game layer.
class QuatreFoil : public Layer
{
public:
	// Parent functions.
	QuatreFoil();
	void OnAttach() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnImGuiRender() override;
	void OnRender() override;

	// Generate floor for the game.
	void generateFloor();
	// Generate dock space for the ImGui panels.
	void generateDockSpace();
	// TEST Spawn new entity in centre of screen.
	void spawnNewEntity();
	// Create player entity.
	void spawnPlayer();

	// Move player by a distance.
	// @param speed: Speed that the player moves by.
	void moveX(float speed);

	// Updates m_FPS every second.
	// @returns Current FPS.
	float GetFPS();
private:

	entt::registry m_registry; // Entity registry.
	Renderer m_renderer; // Renderer object.
	std::unique_ptr<Framebuffer>m_fbo; // Frame buffer. 

	std::unique_ptr<Camera> m_camera; // Camera object.
	glm::vec2 cameraPos = glm::vec2(0.f, 0.f); // Position of camera (world space). 

	std::vector<Quad> m_quads; // All quad's (ie..floors) go here.
	std::shared_ptr<Quad> m_player = std::make_shared<Quad>(m_registry); // Player (kept seperate from other quads).
	
	int quadChoice = 0; // Current entity selected
	bool dockspace_built = false; // Has the dock space been built yet?
	std::vector<std::string> m_entityNames; // Entity names
	std::vector<const char*> m_items; // Entity item
	float fpsTimeAccumulate = 0.0f; // Seconds since last frame update
	float m_fps = 0.0f; // FPS

};