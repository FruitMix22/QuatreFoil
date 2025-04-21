#include "glm.hpp"

// Allows an entity to be moved, rotated, and scaled.
struct Transform
{
	glm::vec2 position = { 0.f, 0.f };
	float rotation = 0.f;
	glm::vec2 scale = { 1.f,1.f };
};