#pragma once

#include <stdio.h>

#include "VanimCore/Window.h"
#include "VanimCore/State.h"

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

		void SwitchState(
			State* state
		);

		Window* GetWindow() { return _window; }
		const Window* GetWindow() const { return _window; }
		const bool IsRunning() const { return _isRunning; }
	private:
		Window*	_window;
		State*	_state;
		bool	_isRunning = false;
		double	_time = 0;
	};
}