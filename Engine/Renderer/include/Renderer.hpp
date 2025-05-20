#pragma once
#include <entt/entt.hpp>
#include "Core/include/EngineCore.hpp"
#include "Buffers/include/VAO.hpp"
#include "Buffers/include/VBO.hpp"
#include "Renderer/include/Texture.hpp"
#include "Components/Renderable.hpp"
#include "Components/RenderLayer.hpp"
#include "Renderer/include/Shader.hpp"
#include "Renderer/include/Camera.hpp"
#include "Buffers/include/FBO.hpp"
#include <memory>

// Renders all available entities.
class Renderer
{
public:
	// Renders all entities with Renderable component.
	// @param registry: registry that all entities are on.
	static void Render(entt::registry& registry);
};