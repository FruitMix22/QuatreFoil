#include "glm.hpp"

// Allows an entity to be moved, rotated, and scaled.
struct Transform
{
	glm::vec2 position = { 0.f, 0.f }; // World position of entity
	float rotation = 0.f; // Rotation of entity
	glm::vec2 scale = { 1.f,1.f }; // Scalar of entity

    // Calculates the model matrix for the model.
    // @returns glm::mat4 Model matrix.
    glm::mat4 GetModelMatrix() const
    {
        glm::mat4 model = glm::mat4(1.0f); // Create model matrix
        // TRS
        model = glm::translate(model, glm::vec3(position.x, -position.y, 0.0f));
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 0, 1));
        model = glm::scale(model, glm::vec3(scale, 1.0f));
        return model;
    }
};