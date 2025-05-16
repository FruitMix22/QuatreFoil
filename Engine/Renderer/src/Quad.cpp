#include "Renderer/include/Quad.hpp"

Quad::Quad(entt::registry& registry) : m_registry(registry){}



void Quad::CreateQuad(glm::vec2 position, glm::vec2 scale)
{
	m_quad = m_registry.create();

	// Create VAO
	m_VAO = std::make_shared<VAO>(m_quadVerts, m_quadIndeces);
	m_VAO->AddVertexBuffer(0, 2, GL_FLOAT, false, sizeof(float) * 4, (void*)0);
	m_VAO->AddVertexBuffer(1, 2, GL_FLOAT, false, sizeof(float) * 4, (void*)(2 * sizeof(float)));
	// Create texture
	// If pointer exists & first character isnt empty
	if (m_imagePath && *m_imagePath)
	{
		m_texture = std::make_shared<Texture>(m_imagePath);
	}
	// Create shader
	m_shader = std::make_shared<Shader>(m_vertexPath, m_fragPath);
	// Set all necessary components.
	auto& renderComp = m_registry.emplace<Renderable>(m_quad);
	auto& transformComp = m_registry.emplace<Transform>(m_quad);

	if(m_texture != nullptr){ renderComp.m_texture = m_texture; }
	renderComp.m_vao = m_VAO;
	renderComp.m_shader = m_shader;
	transformComp.position = position;
	transformComp.scale = scale;
}




