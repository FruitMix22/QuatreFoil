#include <entt/entt.hpp>
#include "Buffers/include/VAO.hpp"
#include "Renderer/include/Texture.hpp"
#include "Renderer/include/Shader.hpp"
#include "Components/Renderable.hpp"
#include "Components/Transform.hpp"

// Creates a standard quad
class Quad
{
public:
	Quad(entt::registry& registry);
	~Quad() {};

	void SetVAO(std::shared_ptr<VAO> vao) { m_VAO = vao; };
	void SetTexture(std::shared_ptr<Texture> texture) { m_texture = texture; }
	void SetShader(std::shared_ptr<Shader> shader) { m_shader = shader; }
	void SetVertexPath(const char* vertPath) { m_vertexPath = vertPath; }
	void SetFragPath(const char* fragPath) { m_fragPath = fragPath; }
	void SetTextureImagePath(const char* imagePath) { m_imagePath = imagePath; }
	
	std::shared_ptr<VAO> GetVAO() { return m_VAO; }
	const char* GetVertexPath() { return m_vertexPath; }
	const char* GetFragPath() { return m_fragPath; }
	entt::entity& GetEntity() { return m_quad; }

	void CreateQuad(glm::vec2 position, glm::vec2 scale);
private:
	entt::registry& m_registry;
	entt::entity m_quad;

	const char* m_vertexPath = "../QuatreFoil/Assets/Shaders/TriangleVert.glsl";
	const char* m_fragPath = "../QuatreFoil/Assets/Shaders/TriangleFrag.glsl";
	const char* m_imagePath = "../QuatreFoil/Assets/Textures/mcgrass.jpg";

	float m_quadVerts[16] =
	{	// x   //y   //u   //v
		-1.f, -1.f, 0.f, 0.f, // bottom-left
		1.0f, -1.f, 1.0f, 0.f, // bottom-right
		1.0f, 1.0f, 1.0f, 1.0f, // top-right
		-1.f, 1.0f, 0.f, 1.0f  // top-left
	};

	unsigned int m_quadIndeces[6] =
	{
		0,1,3,
		1,2,3
	};


	std::shared_ptr<Texture> m_texture;
	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<VAO> m_VAO;
};