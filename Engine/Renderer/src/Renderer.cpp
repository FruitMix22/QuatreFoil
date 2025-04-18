#include "Renderer/include/Renderer.hpp"


void Renderer::Render(entt::registry& registry)
{
	auto view = registry.view<Renderable>();

	for (auto entity : view)
	{
		auto& renderable = view.get<Renderable>(entity);

		renderable.m_vao->Bind();
		renderable.m_shader->Use();

		glViewport(0, 0, 800, 600);


		glDrawArrays(GL_TRIANGLES, 0, renderable.m_vao->GetVertexCount());
	}
}