#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <stdint.h>
#include <glad/glad.h>

namespace Vanim
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void LinkVertexBuffer(
			GLuint vertexBuffer, 
			uint32_t bindingIndex,
			GLenum type,
			GLboolean normalized,
			uint32_t componentCount,
			GLintptr offset,
			GLsizei stride
		);
		
		void LinkIndexBuffer(GLuint indexBuffer);

		void Bind();
		void Unbind();

		bool operator==(const VertexArray& other) { return _id == other._id; }
		bool operator!=(const VertexArray& other) { return !operator==(other); }
		operator GLuint() const { return _id; }
	private:
		GLuint _id;
	};
}
