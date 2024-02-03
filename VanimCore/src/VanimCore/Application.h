#pragma once

#include <stdio.h>

#include "VanimCore/Window.h"

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
			const ApplicationSpecification& spec
		);
		~Application();

		void Run();

		const Window* GetWindow() const { return _window; }
		const bool IsRunning() const { return _isRunning; }
	private:
		Window*	_window;
		bool	_isRunning = false;
	};
}