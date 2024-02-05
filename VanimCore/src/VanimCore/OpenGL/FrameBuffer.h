#pragma once

#include <stdint.h>
#include <glad/glad.h>

namespace Vanim
{
	class FrameBuffer
	{
	public:
		FrameBuffer();
		~FrameBuffer();

		void LinkTexture(
			GLenum attachment,
			GLuint texture
		);

		void Bind();
		void Unbind();

		bool operator==(const FrameBuffer& other) { return _id == other._id; }
		bool operator!=(const FrameBuffer& other) { return !operator==(other); }
		operator GLuint() const { return _id; }
	private:
		GLuint _id;
	};
}
