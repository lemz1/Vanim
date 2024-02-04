#include "vanimpch.h"
#include "VanimCore/Application.h"

namespace Vanim
{
	Application::Application(
		const ApplicationSpecification& spec,
		State* initialState
	)
	{
		_window = new Window(spec.windowSpec);
		_state = initialState;
		_state->Create();
	}

	Application::~Application()
	{
		_state->Destroy();
		delete _state;
		delete _window;
	}

	void Application::Run()
	{
		_isRunning = true;

		while (!glfwWindowShouldClose(_window->_handle))
		{
			glfwPollEvents();

			const double time = glfwGetTime();
			const double deltaTime = time - _time;
			_time = time;

			_state->Update(deltaTime);

			_state->Draw();

			glClearColor(
				0.1f,
				0.1f,
				0.1f,
				1.0f
			);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(_window->_handle);
		}

		_isRunning = false;
	}

	void Application::SwitchState(
		State* state
	)
	{
		_state->Destroy();
		delete _state;
		_state = state;
		_state->Create();
	}
}
