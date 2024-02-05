#pragma once

#include "KeyCode.h"
#include "MouseCode.h"

#include <glm/glm.hpp>

namespace Vanim
{
	class Input
	{
	public:
		static bool JustPressedKey(Key key);
		static bool PressedKey(Key key);
		static bool ReleasedKey(Key key);

		static bool JustPressedMouseButton(MouseButton button);
		static bool PressedMouseButton(MouseButton button);
		static bool ReleasedMouseButton(MouseButton button);
		
		static glm::vec2 GetMousePosition();
	private:
		static bool keyStates[512];
		static bool mouseStates[512];
	};
}
