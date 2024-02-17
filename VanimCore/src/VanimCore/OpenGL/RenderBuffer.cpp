#include "corepch.h"
#include "RenderBuffer.h"

namespace Vanim
{
	RenderBuffer::RenderBuffer(
		uint32_t width, 
		uint32_t height
	)
	:	_id(0)
	{
		glCreateRenderbuffers(1, &_id);

		glNamedRenderbufferStorage(_id, GL_DEPTH_COMPONENT, width, height);
	}

	RenderBuffer::~RenderBuffer()
	{
		glDeleteRenderbuffers(1, &_id);
		_id = 0;
	}
}
