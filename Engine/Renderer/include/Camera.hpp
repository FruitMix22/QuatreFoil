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

	// Returns view matrix.
	glm::mat4 GetViewMatrix();
	// Returns projecion matrix.
	glm::mat4 GetProjectionMatrix();

	// Sets camera position.
	// @param newPos: New position for camera.
	void Setposition(glm::vec2 newPos) { m_position = newPos; }
	// Sets camera perspective.
	// @param newPerspective: New perspective for camera.
	void SetPerspective(glm::vec2 newPerspective) { m_perspective = newPerspective; }
private:
	glm::vec2 m_position = glm::vec2(0.f); // Camera pos
	glm::vec2 m_perspective = glm::vec2(800.f, 600.f); // Camera perspective
	entt::entity m_camera; // Camera entity
};