#include "Renderer/include/Renderer.hpp"
#include "Core/include/EngineCore.hpp"
#include "Buffers/include/VAO.hpp"
#include "Buffers/include/VBO.hpp"
#include "Components/Renderable.cpp"

void Renderer::Render(entt::registry& registry)
{
	auto view = registry.view<Renderable>();

	for (auto entity : view)
	{
		auto& renderable = view.get<Renderable>(entity);

		renderable.m_vao.Bind();

		glDrawArrays(GL_TRIANGLES, 0, renderable.m_vertexCount);
	}
}