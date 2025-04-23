#pragma once
#include <../glm/gtc/matrix_transform.hpp>

struct Camera
{
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec2 perspective = glm::vec2(800.f, 600.f); // ortho for now
	
    glm::mat4 GetViewMatrix() const
    {
        return glm::mat4(1.0f); // We aint schmmoooooovin yet
    }

    glm::mat4 GetProjectionMatrix() const
    {
        return glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    }
};