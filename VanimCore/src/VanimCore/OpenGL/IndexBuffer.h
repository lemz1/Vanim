#pragma once

#include <stdint.h>
#include <glad/glad.h>

namespace Vanim
{
	class IndexBuffer
	{
	public:
		IndexBuffer() = default;
		IndexBuffer(
			GLsizeiptr size,
			const void* data
		);
		~IndexBuffer();

		void Bind();
		void Unbind();

		bool operator==(const IndexBuffer& other) { return _id == other._id; }
		bool operator!=(const IndexBuffer& other) { return !operator==(other); }
		operator GLuint() const { return _id; }
	private:
		GLuint _id;
	};
}
