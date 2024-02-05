#include "corepch.h"
#include "VertexBuffer.h"

namespace Vanim
{
	VertexBuffer::VertexBuffer(
		GLsizeiptr size,
		const void* data
	)
	:	_id(0)
	{
		glCreateBuffers(1, &_id);
		glNamedBufferData(_id, size, data, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &_id);
		_id = 0;
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _id);
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
