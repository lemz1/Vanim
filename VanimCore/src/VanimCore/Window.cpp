#include "vanimpch.h"
#include "VanimCore/Window.h"

#include <stdio.h>
#include <assert.h>

static void glfwErrorCallback(
	int			error_code, 
	const char* description
)
{
	fprintf(stderr, "GLFW ERROR %d: %s\n", error_code, description);
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
	fprintf(stderr, "OpenGL Debug Message: %s\n", message);
	#if VANIM_DEBUG
	assert(false);
	#endif
}

namespace Vanim
{
	Window::Window(
		const WindowSpecification& spec
	)
		: _title(spec.title),
		_width(spec.width),
		_height(spec.height),
		_vSync(spec.vSync)
	{
		if (!glfwInit())
		{
			fprintf(stderr, "Could not init glfw!\n");
			return;
		}

		glfwSetErrorCallback(glfwErrorCallback);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		_handle = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
		if (!_handle)
		{
			fprintf(stderr, "Could not create glfw window!\n");
			glfwTerminate();
			return;
		}


		glfwMakeContextCurrent(_handle);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			fprintf(stderr, "Could not initialize glad!\n");
			glfwTerminate();
			return;
		}

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
