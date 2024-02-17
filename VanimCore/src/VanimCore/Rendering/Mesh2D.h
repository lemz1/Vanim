#pragma once

#include "VanimCore/Base.h"

#include <vector>
#include <glm/glm.hpp>

#include "VanimCore/OpenGL/VertexArray.h"
#include "VanimCore/OpenGL/Shader.h"

namespace Vanim
{
	class Mesh2D
	{
	public:
		Mesh2D() = default;
		Mesh2D(
			std::vector<glm::vec2> vertices,
			std::vector<glm::vec2> texCoords,
			std::vector<GLuint> indices,
			const Shared<Shader>& shader
		);
	private:
		std::vector<glm::vec2> _vertices;
		std::vector<glm::vec2> _texCoords;
		std::vector<GLuint> _indices;

		Unique<VertexArray> _vao;
		Unique<VertexBuffer> _vbo, _tcbo;
		Unique<IndexBuffer> _ibo;

		Shared<Shader> _shader;

		friend class Renderer;
	};
}
