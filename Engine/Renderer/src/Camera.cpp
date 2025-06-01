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
	float halfW = (m_perspective.x / m_zoom) * 0.5f;
	float halfH = (m_perspective.y / m_zoom) * 0.5f;

	glm::mat4 view(1.0f);

	// Since Y axis is flipped in projection, add halfH to Y to center properly
	view = glm::translate(view, glm::vec3(-m_truePos.x + halfW, -m_truePos.y + halfH, 0.0f));

	return view;
}





glm::mat4 Camera::GetProjectionMatrix()
{
	float halfW = (m_perspective.x / m_zoom) * 0.5f;
	float halfH = (m_perspective.y / m_zoom) * 0.5f;

	return glm::ortho(-halfW, halfW, halfH, -halfH, -1.0f, 1.0f);

}

glm::vec2 Camera::GetPerspective()
{
	return m_perspective;
}

glm::vec2 Camera::GetPosition()
{
	return m_truePos - glm::vec2(500.f,600.f);
}
