#include "corepch.h"
#include "Mesh.h"

namespace Vanim
{
	Mesh::Mesh(
		std::vector<glm::vec2> vertices, 
		std::vector<glm::vec2> texCoords,
		std::vector<GLuint> indices
	)
	:	_vertices(vertices),
		_texCoords(texCoords),
		_indices(indices)
	{
		_vao = MakeShared<VertexArray>();

		_vbo = MakeShared<VertexBuffer>(sizeof(glm::vec2) * _vertices.size(), _vertices.data());
		_tcbo = MakeShared<VertexBuffer>(sizeof(glm::vec2) * _texCoords.size(), _texCoords.data());

		_ibo = MakeShared<IndexBuffer>(sizeof(GLuint) * _indices.size(), _indices.data());
	}
}
