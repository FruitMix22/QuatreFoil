#pragma once
#include <entt/entt.hpp>
#include "Buffers/include/VAO.hpp"
#include "Renderer/include/Texture.hpp"
#include "Renderer/include/Shader.hpp"
#include "Components/Renderable.hpp"
#include "Components/Transform.hpp"

// Creates a standard quad.
class Quad
{
public:
	// Copies registry reference.
	Quad(entt::registry& registry);
	~Quad() {};

	// Sets VAO.
	// @param vao: new VAO.
	void SetVAO(std::shared_ptr<VAO> vao) { m_VAO = vao; };
	// Sets texture.
	// @param texture: new Texture.
	void SetTexture(std::shared_ptr<Texture> texture) { m_texture = texture; }
	// Sets shader.
	// @param shader: new shader.
	void SetShader(std::shared_ptr<Shader> shader) { m_shader = shader; }
	// Sets Vertex shader path.
	// @param vertPath: path for vertex shader.
	void SetVertexPath(const char* vertPath) { m_vertexPath = vertPath; }
	// Sets fragment shader path.
	// @param fragPath: path for fragment shader.
	void SetFragPath(const char* fragPath) { m_fragPath = fragPath; }
	// Sets path for image.
	// @param imagePath: path for texture.
	void SetTextureImagePath(const char* imagePath) { m_imagePath = imagePath; }
	
	// @returns shared_ptr<VAO>.
	std::shared_ptr<VAO> GetVAO() { return m_VAO; }
	// @returns const char* VertexPath.
	const char* GetVertexPath() { return m_vertexPath; }
	// @returns const char* FragPath.
	const char* GetFragPath() { return m_fragPath; }
	// @returns entt::entity& Entity.
	entt::entity& GetEntity() { return m_quad; }

	// Creates the quad and handles all VAO/Shader/Texture calls.
	// @param position: World space position for quad.
	// @param scale: Scale for quad.
	void CreateQuad(glm::vec2 position, glm::vec2 scale);
private:
	entt::registry& m_registry; // Registry that holds all entities
	entt::entity m_quad; // Quad entity id

	const char* m_vertexPath = "../QuatreFoil/Assets/Shaders/TriangleVert.glsl";
	const char* m_fragPath = "../QuatreFoil/Assets/Shaders/TriangleFrag.glsl";
	const char* m_imagePath = "";

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