#pragma once
#include "Core/include/Layer.hpp"
#include <entt/entt.hpp>
#include "Buffers/include/VAO.hpp"
#include "Buffers/include/VBO.hpp"
#include "Renderer/include/Renderer.hpp"
#include "Renderer/include/Shader.hpp"
#include "Components/Renderable.hpp"


class QuatreFoil : public Layer
{
private:
	entt::registry m_registry;
	Renderer m_renderer;
	float triangleColour[4] = { 1, 0, 1, 0 };
	
public:
	QuatreFoil() {}; // Default constructor
	void OnAttach() override;
	void OnUpdate() override;
	void OnImGuiRender() override;
	void OnRender() override;

	void generateEntities();
};