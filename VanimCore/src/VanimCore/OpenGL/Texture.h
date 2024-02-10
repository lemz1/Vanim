#pragma once

#include <stdint.h>
#include <glad/glad.h>

namespace Vanim
{
	class Texture
	{
	public:
		Texture() = default;
		Texture(
			uint32_t width,
			uint32_t height
		);
		~Texture();

		void Bind();
		void Unbind();

		void SetViewport();

		bool operator==(const Texture& other) { return _id == other._id; }
		bool operator!=(const Texture& other) { return !operator==(other); }
		operator GLuint() const { return _id; }

		uint32_t GetWidth() const { return _width; }
		uint32_t GetHeight() const { return _height; }
	private:
		GLuint _id;
		uint32_t _width, _height;
	};
}
