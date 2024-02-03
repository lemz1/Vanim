#include "VanimCore/Window/Window.h"

#include <stdio.h>

Window createWindow(WindowSpecification* spec) 
{
	Window window;
	window._windowHandle = 0;
	window._spec = *spec;

	if (!glfwInit()) 
	{
		printf("Could not init glfw!\n");
		return window;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window._windowHandle = glfwCreateWindow(spec->width, spec->height, spec->title, 0, 0);
	if (!window._windowHandle) 
	{
		printf("Could not create glfw window!\n");
		glfwTerminate();
		return window;
	}

	glfwMakeContextCurrent(window._windowHandle);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Could not initialize glad!\n");
		glfwTerminate();
		return window;
	}

	return window;
}
