#include "corepch.h"
#include "IndexBuffer.h"

namespace Vanim
{
	IndexBuffer::IndexBuffer(
		GLsizeiptr size, 
		const void* data
	)
	:	_id(0)
	{
		glCreateBuffers(1, &_id);
		glNamedBufferData(_id, size, data, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &_id);
		_id = 0;
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
	}

	void IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
