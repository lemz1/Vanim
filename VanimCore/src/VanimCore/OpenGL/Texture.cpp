#include "corepch.h"
#include "Texture.h"

namespace Vanim
{
	Texture::Texture(
		uint32_t width,
		uint32_t height
	)
	:	_id(0),
		_width(width),
		_height(height)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &_id);

		glBindTexture(GL_TEXTURE_2D, _id);

		glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &_id);
		_id = 0;
	}

	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, _id);
	}

	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::SetViewport()
	{
		glViewport(0, 0, _width, _height);
	}
}
