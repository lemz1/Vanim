#pragma once

#include "KeyCode.h"
#include "MouseCode.h"

#include <glm/glm.hpp>

namespace Vanim
{
	class Input
	{
	public:
		// needs to be called somewhere in the main loop
		static void UpdateStates();

		static bool JustPressedKey(Key key);
		static bool PressedKey(Key key);
		static bool ReleasedKey(Key key);

		static bool JustPressedMouseButton(MouseButton button);
		static bool PressedMouseButton(MouseButton button);
		static bool ReleasedMouseButton(MouseButton button);
		
		static glm::vec2 GetMousePosition();
	};
}
