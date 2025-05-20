#include "Renderer/include/Renderer.hpp"


void Renderer::Render(entt::registry& registry)
{
	// Setup camera
	auto cameraView = registry.view<Camera>();
	for (auto entity : cameraView)
	{
		auto& camera = cameraView.get<Camera>(entity);
		glViewport(0, 0, camera.GetPerspective().x, camera.GetPerspective().y);
	}

	// Create render buckets by layer
	std::array<std::vector<entt::entity>, NUM_RENDER_LAYERS> renderBuckets;

	// Bucket all renderables by their layer
	auto renderView = registry.view<Renderable, RenderLayer>();
	for (auto entity : renderView)
	{
		auto& layer = renderView.get<RenderLayer>(entity);
		int layerIndex = static_cast<int>(layer);

		if (layerIndex >= 0 && layerIndex < NUM_RENDER_LAYERS)
		{
			renderBuckets[layerIndex].push_back(entity);
		}
	}

	// Render each layer in order
	for (int i = 0; i < NUM_RENDER_LAYERS; ++i)
	{
		for (auto entity : renderBuckets[i])
		{
			auto& renderable = registry.get<Renderable>(entity);

			renderable.m_vao->Bind();
			renderable.m_shader->Use();

			if (renderable.m_texture)
				renderable.m_texture->Bind();

			glDrawElements(GL_TRIANGLES, renderable.m_vao->GetIndicesCount(), GL_UNSIGNED_INT, 0);

			renderable.m_vao->Unbind();
			if (renderable.m_texture)
				renderable.m_texture->Unbind();
		}
	}
}
