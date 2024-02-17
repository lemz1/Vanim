#include "corepch.h"
#include "Mesh2D.h"

namespace Vanim
{
	Mesh2D::Mesh2D(
		std::vector<glm::vec2> vertices, 
		std::vector<glm::vec2> texCoords,
		std::vector<GLuint> indices,
		const Shared<Shader>& shader
	)
	:	_vertices(vertices),
		_texCoords(texCoords),
		_indices(indices),
		_shader(shader)
	{
		_vao = MakeUnique<VertexArray>();

		_vbo = MakeUnique<VertexBuffer>(sizeof(glm::vec2) * _vertices.size(), _vertices.data());
		_tcbo = MakeUnique<VertexBuffer>(sizeof(glm::vec2) * _texCoords.size(), _texCoords.data());

		_ibo = MakeUnique<IndexBuffer>(sizeof(GLuint) * _indices.size(), _indices.data());
	}
}
