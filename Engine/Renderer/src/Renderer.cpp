#include "Renderer/include/Renderer.hpp"


void Renderer::Render(entt::registry& registry)
{
	// Set viewport
	// TODO: Change this to be done by camera when added.
	glViewport(0, 0, 800, 600);

	// Get all entities with a renderable component
	auto view = registry.view<Renderable>();

	for (auto entity : view)
	{
		auto& renderable = view.get<Renderable>(entity);

		renderable.m_vao->Bind();
		renderable.m_shader->Use();

		glDrawElements(GL_TRIANGLES, renderable.m_vao->GetIndicesCount(), GL_UNSIGNED_INT, 0);

		// Not strictly neccesary but okay for now
		// (will be overwritten by other bindings when drawing more)
		renderable.m_vao->Unbind();

	}
}