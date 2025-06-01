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

// This file defines ExampleGame layer, inheriting from Layer.
/*
 This class and demonstration shows how this game engine can be used.
 Layer is just a base class that has functions that can be called directly in the engine loop.
 All the overidden functions are functions that are called in the engine loop.
*/
class ExampleGame : public Layer
{
public:
	
	// Called when creating the game.
	// Good to initialise members here.
	ExampleGame();

	// The next group of functions are called in chronological order.

	// Called when first attatching to the engine.
	void OnAttach() override;

	// Called when the game is starting.
	void OnStart() override;

	// Called every frame first.
	void OnUpdate() override;

	//Called to render any entities with a Renderable component.
	void OnRender() override;

	// Called  to render any ImGui elements.
	void OnImGuiRender() override;

	// These are now functions that have been wrote to show an example of a quad being drawn.

	// Return FPS.
	// Calculates by time accumulated between frames.
	float GetFPS();

	// Generates a rectangle entity with a Renderable and Transform component.
	void GenerateRectangle();

	// Moves the Square via its Transform component.
	void MoveSquareWithA(float dt);
	void MoveSquareWithD(float dt);

private:
	entt::registry m_registry; // Entity registry.
	Renderer m_renderer; // Renderer object.
	std::unique_ptr<Framebuffer>m_fbo; // Frame buffer. 

	std::unique_ptr<Camera> m_camera; // Camera object.
	glm::vec2 cameraPos = glm::vec2(0.f, 0.f); // Position of camera (world space). 

	float fpsTimeAccumulate = 0.0f; // Seconds since last frame update.
	float m_fps = 0.0f; // FPS.

	glm::vec4 m_rectangleColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);  // Colour of rectangle.

};