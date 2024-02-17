#pragma once

#include <stdint.h>
#include <glad/glad.h>

namespace Vanim
{
	class RenderBuffer
	{
	public:
		RenderBuffer() = default;
		RenderBuffer(
			uint32_t width,
			uint32_t height
		);
		~RenderBuffer();

		bool operator==(const RenderBuffer& other) { return _id == other._id; }
		bool operator!=(const RenderBuffer& other) { return !operator==(other); }
		operator GLuint() const { return _id; }
	private:
		GLuint _id;
	};
}
