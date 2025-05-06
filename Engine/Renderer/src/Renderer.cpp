#include "Renderer/include/Renderer.hpp"


void Renderer::Render(entt::registry& registry)
{
	// Set viewport
	// TODO: Change this to be done by camera when added.
	auto view = registry.view<Camera>();
	for (auto entity : view)
	{
		auto& camera = view.get<Camera>(entity);
		glViewport(0, 0, camera.GetPerspective().x, camera.GetPerspective().y);
	}

	// Get all entities with a renderable component
	auto view2 = registry.view<Renderable>();

	for (auto entity : view2)
	{
		auto& renderable = view2.get<Renderable>(entity);

		renderable.m_vao->Bind();
		renderable.m_shader->Use();

		if (renderable.m_texture != nullptr)
		{
			renderable.m_texture->Bind();
		}

		glDrawElements(GL_TRIANGLES, renderable.m_vao->GetIndicesCount(), GL_UNSIGNED_INT, 0);

		// Not strictly neccesary but okay for now
		// (will be overwritten by other bindings when drawing more)
		renderable.m_vao->Unbind();

	}
}