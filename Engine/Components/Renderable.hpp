#pragma once
#include <memory>

// Forward declare
class VAO;
class Shader;
class Texture;

// Allows an entity to be rendered.
// Requires a VAO and a shader.
struct Renderable
{
	std::shared_ptr<VAO> m_vao{ nullptr }; // Empty VAO pointer.
	std::shared_ptr<Shader> m_shader{ nullptr }; // Empty shader pointer.
	std::shared_ptr<Texture> m_texture{ nullptr }; // Empty texture pointer.
};