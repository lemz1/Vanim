#include "VanimCore/Application/Application.h"

void createApplication(ApplicationSpecification* spec)
{
	g_Window = createWindow(&spec->windowSpec);
}

void runApplication()
{
	g_IsRunning = true;

	while (!glfwWindowShouldClose(g_Window._windowHandle))
	{
		glfwPollEvents();
	}

	g_IsRunning = false;
}

void endApplication()
{
	glfwTerminate();
}
