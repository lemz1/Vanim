#include "corepch.h"
#include "Input.h"

#include "VanimCore/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Vanim
{
	bool Input::keyStates[512] = { false };
	bool Input::mouseStates[512] = { false };

	bool Input::JustPressedKey(Key key)
	{
		if (keyStates[(KeyCode)key])
		{
			return false;
		}
		
		if (glfwGetKey(Application::GetWindow()->GetHandle(), (KeyCode)key) == GLFW_PRESS)
		{
			keyStates[(KeyCode)key] = true;
			return true;
		}

		return false;
	}

	bool Input::PressedKey(Key key)
	{
		if (glfwGetKey(Application::GetWindow()->GetHandle(), (KeyCode)key) == GLFW_PRESS)
		{
			keyStates[(KeyCode)key] = true;
			return true;
		}

		return false;
	}

	bool Input::ReleasedKey(Key key)
	{
		if (!keyStates[(KeyCode)key])
		{
			return false;
		}

		if (glfwGetKey(Application::GetWindow()->GetHandle(), (KeyCode)key) == GLFW_RELEASE)
		{
			keyStates[(KeyCode)key] = false;
			return true;
		}

		return false;
	}

	bool Input::JustPressedMouseButton(MouseButton button)
	{
		if (mouseStates[(MouseCode)button])
		{
			return false;
		}

		if (glfwGetMouseButton(Application::GetWindow()->GetHandle(), (MouseCode)button) == GLFW_PRESS)
		{
			mouseStates[(MouseCode)button] = true;
			return true;
		}

		return false;
	}

	bool Input::PressedMouseButton(MouseButton button)
	{
		if (glfwGetMouseButton(Application::GetWindow()->GetHandle(), (MouseCode)button) == GLFW_PRESS)
		{
			mouseStates[(MouseCode)button] = true;
			return true;
		}

		return false;
	}

	bool Input::ReleasedMouseButton(MouseButton button)
	{
		if (!mouseStates[(MouseCode)button])
		{
			return false;
		}

		if (glfwGetMouseButton(Application::GetWindow()->GetHandle(), (MouseCode)button) == GLFW_RELEASE)
		{
			mouseStates[(MouseCode)button] = false;
			return true;
		}

		return false;
	}

	glm::vec2 Input::GetMousePosition()
	{
		double x, y;
		glfwGetCursorPos(Application::GetWindow()->GetHandle(), &x, &y);
		return glm::vec2(x, y);
	}
}
