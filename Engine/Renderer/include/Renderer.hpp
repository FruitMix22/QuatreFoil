#pragma once
#include <entt/entt.hpp>
#include "Core/include/EngineCore.hpp"
#include "Buffers/include/VAO.hpp"
#include "Buffers/include/VBO.hpp"
#include "Components/Renderable.hpp"
#include "Renderer/include/Shader.hpp"
#include <memory>

class Renderer
{

public:

	static void Render(entt::registry& registry);

};