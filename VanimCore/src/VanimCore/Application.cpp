#include "vanimpch.h"
#include "VanimCore/Application.h"

namespace Vanim
{
	Application::Application(
		const ApplicationSpecification& spec
	)
	{
		_window = new Window(spec.windowSpec);
	}

	Application::~Application()
	{
		delete _window;
	}

	void Application::Run()
	{
		_isRunning = true;

		while (!glfwWindowShouldClose(_window->GetHandle()))
		{
			glfwPollEvents();

			glClearColor(
				0.1f,
				0.1f,
				0.1f,
				1.0f
			);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(_window->GetHandle());
		}

		_isRunning = false;
	}
}
