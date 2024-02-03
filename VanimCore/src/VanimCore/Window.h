#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Vanim
{
	struct WindowSpecification
	{
		const char* title;
		uint32_t	width;
		uint32_t	height;
		bool		vSync;
	};

	class Window
	{
	public:
		Window() = default;
		Window(
			const WindowSpecification& spec
		);
		~Window();

		const GLFWwindow* GetHandle() const { return _handle; }
		GLFWwindow* GetHandle() { return _handle; }

		const char* GetTitle() const { return _title; }

		const uint32_t GetWidth() const { return _width; }

		const uint32_t GetHeight() const { return _height; }

		const bool VSync() const { return _vSync; }
	private:
		GLFWwindow* _handle;
		const char*	_title;
		uint32_t	_width;
		uint32_t	_height;
		bool		_vSync;
	};
}
