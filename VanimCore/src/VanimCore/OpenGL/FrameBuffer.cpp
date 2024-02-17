#include "corepch.h"
#include "FrameBuffer.h"

namespace Vanim
{
	FrameBuffer::FrameBuffer()
	:	_id(0)
	{
		glCreateFramebuffers(1, &_id);
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &_id);
		_id = 0;
	}

	void FrameBuffer::LinkTexture(
		GLenum attachment,
		GLuint texture
	)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _id);

		glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _id);
	}

	void FrameBuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::Clear(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}
