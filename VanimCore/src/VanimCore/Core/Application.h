#pragma once

#include <stdio.h>

#include "Window.h"
#include "State.h"

namespace Vanim
{
	struct ApplicationSpecification
	{
		WindowSpecification	windowSpec;
	};

	class Application
	{
	public:
		Application(
			const ApplicationSpecification& spec,
			State* initialState
		);
		~Application();

		void Run();

		static void SwitchState(State* state);

		static Window* GetWindow() { return _instance->_window; }
		static bool IsRunning() { return _instance->_isRunning; }

		static float GetTime() { return _instance->_time; }
	private:
		static Application* _instance;

		Window*	_window = nullptr;
		State*	_state = nullptr;
		bool	_isRunning = false;
		float	_time = 0;
	};
}