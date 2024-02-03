#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdbool.h>

typedef struct 
{
	const char* title;
	uint32_t	width;
	uint32_t	height;
	bool		vSync;
} WindowSpecification;

typedef struct 
{
	GLFWwindow*			_windowHandle;
	WindowSpecification _spec;
} Window;

Window createWindow(WindowSpecification* spec);
