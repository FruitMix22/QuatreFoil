#pragma once
#include "Renderer/include/Camera.hpp"

Camera::Camera(entt::registry& registry)
{
	m_camera = registry.create();
}

Camera::~Camera()
{

}

glm::mat4 Camera::GetViewMatrix()
{
	glm::mat4 view(1.f);
	return view = glm::translate(view, glm::vec3(-m_position.x, m_position.y, 0.f));
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::ortho(0.0f, m_perspective.x, m_perspective.y, 0.0f, -1.0f, 1.0f);
}

glm::vec2 Camera::GetPerspective()
{
	return m_perspective;
}
