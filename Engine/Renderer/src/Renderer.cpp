#include "Renderer/include/Renderer.hpp"


void Renderer::Render(entt::registry& registry)
{
	glViewport(0, 0, 800, 600);

	auto view = registry.view<Renderable>();

	for (auto entity : view)
	{
		auto& renderable = view.get<Renderable>(entity);

		renderable.m_vao->Bind();
		renderable.m_vao->m_vbo->Bind();
		renderable.m_vao->m_ebo->Bind();
		renderable.m_shader->Use();

		//std::cout << renderable.m_vao->GetIndicesCount() << std::endl;
		glDrawElements(GL_TRIANGLES, renderable.m_vao->GetIndicesCount(), GL_UNSIGNED_INT, 0);

		//renderable.m_vao->Unbind();


		//glDrawArrays(GL_TRIANGLES, 0, renderable.m_vao->GetVertexCount());
	}
}