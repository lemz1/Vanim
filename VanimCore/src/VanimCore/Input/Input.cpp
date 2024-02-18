#include "corepch.h"
#include "Input.h"

#include "VanimCore/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Vanim
{
	bool previousKeyStates[512] = { false };
	bool currentKeyStates[512] = { false };

	bool previousMouseStates[32] = { false };
	bool currentMouseStates[32] = { false };

	void Input::UpdateStates()
	{
		memcpy(previousKeyStates, currentKeyStates, sizeof(currentKeyStates));
	}

	bool Input::JustPressedKey(Key key)
	{
		GLFWwindow* window = Application::GetWindow()->GetHandle();
		KeyCode keyCode = (KeyCode)key;

		currentKeyStates[keyCode] = glfwGetKey(window, keyCode) == GLFW_PRESS;
		
		if (previousKeyStates[keyCode])
		{
			return false;
		}
		
		return currentKeyStates[keyCode];
	}

	bool Input::PressedKey(Key key)
	{
		GLFWwindow* window = Application::GetWindow()->GetHandle();
		KeyCode keyCode = (KeyCode)key;

		currentKeyStates[keyCode] = glfwGetKey(window, keyCode) == GLFW_PRESS;

		return currentKeyStates[keyCode];
	}

	bool Input::ReleasedKey(Key key)
	{
		GLFWwindow* window = Application::GetWindow()->GetHandle();
		KeyCode keyCode = (KeyCode)key;

		currentKeyStates[keyCode] = glfwGetKey(window, keyCode) == GLFW_PRESS;

		if (!previousKeyStates[keyCode])
		{
			return false;
		}

		return !currentKeyStates[keyCode];
	}

	bool Input::JustPressedMouseButton(MouseButton button)
	{
		GLFWwindow* window = Application::GetWindow()->GetHandle();
		MouseCode mouseCode = (MouseCode)button;

		currentMouseStates[mouseCode] = glfwGetMouseButton(window, mouseCode) == GLFW_PRESS;

		if (previousMouseStates[mouseCode])
		{
			return false;
		}

		return currentMouseStates[mouseCode];
	}

	bool Input::PressedMouseButton(MouseButton button)
	{
		GLFWwindow* window = Application::GetWindow()->GetHandle();
		MouseCode mouseCode = (MouseCode)button;

		currentMouseStates[mouseCode] = glfwGetMouseButton(window, mouseCode) == GLFW_PRESS;

		return currentMouseStates[mouseCode];
	}

	bool Input::ReleasedMouseButton(MouseButton button)
	{
		GLFWwindow* window = Application::GetWindow()->GetHandle();
		MouseCode mouseCode = (MouseCode)button;

		currentMouseStates[mouseCode] = glfwGetMouseButton(window, mouseCode) == GLFW_PRESS;

		if (!previousMouseStates[mouseCode])
		{
			return false;
		}

		return !currentMouseStates[mouseCode];
	}

	glm::vec2 Input::GetMousePosition()
	{
		double x, y;
		glfwGetCursorPos(Application::GetWindow()->GetHandle(), &x, &y);
		return glm::vec2(x, y);
	}
}
