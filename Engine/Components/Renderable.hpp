#pragma once
#include <memory>

class VAO;
class Shader;

struct Renderable
{
	std::shared_ptr<VAO> m_vao{ nullptr };
	std::shared_ptr<Shader> m_shader{ nullptr };
};