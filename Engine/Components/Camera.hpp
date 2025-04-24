#pragma once
#include <../glm/gtc/matrix_transform.hpp>

struct Camera
{
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 perspective = glm::vec2(800.f, 600.f); // ortho for now
	
    glm::mat4 GetViewMatrix() const
    {
        glm::mat4 view(1.0f); 
        return view = glm::translate(view, glm::vec3(-position.x, position.y, 0.f));
    }

    glm::mat4 GetProjectionMatrix() const
    {
        return glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    }
};