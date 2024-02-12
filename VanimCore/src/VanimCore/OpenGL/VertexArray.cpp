#include "corepch.h"
#include "VertexArray.h"

namespace Vanim
{
	VertexArray::VertexArray()
	:	_id(0)
	{
		glCreateVertexArrays(1, &_id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &_id);
		_id = 0;
	}

	void VertexArray::LinkVertexBuffer(
		GLuint vertexBuffer,
		uint32_t bindingIndex,
		GLenum type,
		GLboolean normalized,
		uint32_t componentCount,
		GLintptr offset,
		GLsizei stride
	)
	{
		glBindVertexArray(_id);

		glVertexAttribPointer(
			bindingIndex, 
			componentCount, 
			type, 
			normalized, 
			stride, 
			nullptr
		);
		glEnableVertexAttribArray(bindingIndex);

		glVertexArrayVertexBuffer(_id, bindingIndex, vertexBuffer, offset, stride);

		glBindVertexArray(0);
	}

	void VertexArray::LinkIndexBuffer(GLuint indexBuffer)
	{
		glVertexArrayElementBuffer(_id, indexBuffer);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(_id);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}
}
