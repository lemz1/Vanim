#pragma once

#include <stdint.h>
#include <glad/glad.h>

namespace Vanim
{
	class VertexBuffer
	{
	public:
		VertexBuffer() = default;
		VertexBuffer(
			GLsizeiptr size,
			const void* data
		);
		~VertexBuffer();

		void Bind();
		void Unbind();

		bool operator==(const VertexBuffer& other) { return _id == other._id; }
		bool operator!=(const VertexBuffer& other) { return !operator==(other); }
		operator GLuint() const { return _id; }
	private:
		GLuint _id;
	};
}
