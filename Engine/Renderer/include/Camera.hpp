#pragma once
#include <entt/entt.hpp>
#include "glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"


// Simple camera system
class Camera
{
public:
	// Adds entity to the registry.
	// @param registry: Game entity registry.
	Camera(entt::registry& registry);

	// Default destructor.
	~Camera();

	// @returns glm::mat4 view matrix.
	glm::mat4 GetViewMatrix();
	// @returns glm::mat4 projecion matrix.
	glm::mat4 GetProjectionMatrix();
	// @returns glm::vec2 perspective
	glm::vec2 GetPerspective();
	// @returns glm::vec2 position.
	glm::vec2 GetPosition();

	// Sets camera position.
	// @param newPos: New position for camera.
	void Setposition(glm::vec2 newPos) { m_truePos = newPos + glm::vec2(500.f,600.f); }
	// Sets camera perspective.
	// @param newPerspective: New perspective for camera.
	void SetPerspective(glm::vec2 newPerspective) { m_perspective = newPerspective; }
	float m_zoom = 1.5f;
	glm::vec2 m_truePos = glm::vec2(500.f, 600.f); // true location (top left)
private:
	glm::vec2 m_perspective = glm::vec2(1920.f, 1080.f); // Camera perspective
	entt::entity m_camera; // Camera entity
};