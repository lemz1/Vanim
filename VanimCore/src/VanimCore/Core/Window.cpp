#include "corepch.h"
#include "Window.h"

#include <iostream>
#include <cassert>

#include "VanimCore/Base.h"

static void glfwErrorCallback(
	int			error_code, 
	const char* description
)
{
	VANIM_ERROR("GLFW ERROR " << error_code << ": " << description);
}

static void APIENTRY openglDebugCallback(
	GLenum			source,
	GLenum			type,
	GLuint			id,
	GLenum			severity,
	GLsizei			length,
	const GLchar*	message,
	const void*		userParam
)
{
	switch (severity)
	{
		case GL_DEBUG_SEVERITY_MEDIUM:
		case GL_DEBUG_SEVERITY_HIGH:
			VANIM_ERROR("OpenGL Debug Message: " << message);
			#ifdef VANIM_DEBUG
			assert(severity != GL_DEBUG_SEVERITY_HIGH);
			#endif
			break;
		default:
			return;
	}
}

namespace Vanim
{
	Window::Window(const WindowSpecification& spec)
	:	_title(spec.title),
		_width(spec.width),
		_height(spec.height),
		_vSync(spec.vSync)
	{
		if (!glfwInit())
		{
			VANIM_ERROR("Could not init glfw!");
			return;
		}

		glfwSetErrorCallback(glfwErrorCallback);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		_handle = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
		if (!_handle)
		{
			VANIM_ERROR("Could not create glfw window!");
			glfwTerminate();
			return;
		}


		glfwMakeContextCurrent(_handle);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			VANIM_ERROR("Could not initialize glad!");
			glfwTerminate();
			return;
		}

		glViewport(0, 0, _width, _height);
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(openglDebugCallback, nullptr);
	}

	Window::~Window()
	{
		glfwDestroyWindow(_handle);
		glfwTerminate();
	}
}
