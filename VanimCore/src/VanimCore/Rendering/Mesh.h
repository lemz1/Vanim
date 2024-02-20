#pragma once

#include "VanimCore/Base.h"

#include <vector>
#include <glm/glm.hpp>

#include "VanimCore/OpenGL/VertexArray.h"
#include "VanimCore/OpenGL/Shader.h"

namespace Vanim
{
	class Mesh
	{
	public:
		Mesh() = default;
		Mesh(
			std::vector<glm::vec2> vertices,
			std::vector<glm::vec2> texCoords,
			std::vector<GLuint> indices
		);

		const Shared<VertexArray>& GetVAO() const { return _vao; }
		const GLsizei NumIndices() const { return _indices.size(); }
	private:
		std::vector<glm::vec2> _vertices;
		std::vector<glm::vec2> _texCoords;
		std::vector<GLuint> _indices;

		Shared<VertexArray> _vao;
		Shared<VertexBuffer> _vbo;
		Shared<VertexBuffer> _tcbo;
		Shared<IndexBuffer> _ibo;

		friend class Renderer;
	};
}
