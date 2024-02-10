#include "editorpch.h"
#include "CameraController.h"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace Vanim
{
	void CameraController::Update(const float deltaTime)
	{
		glm::vec2 mousePos = Input::GetMousePosition();
		glm::vec2 deltaMousePos = mousePos - _lastMousePos;
		_lastMousePos = mousePos;

		// this needs to be here because else on the first frame the deltaMousePos could be crazy
		static bool firstTime = true;
		if (firstTime)
		{
			firstTime = false;
			glfwSetInputMode(Application::GetWindow()->GetHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			deltaMousePos = glm::vec2(0.f);
		}

		if (!HasAllOf<TransformComponent, CameraComponent>())
		{
			return;
		}

		auto [tc, cc] = GetComponents<TransformComponent, CameraComponent>();

		auto& transform = tc.get();
		auto& camera = cc.get().camera;

		if (camera.IsOrthographic())
		{
			OrthographicUpdate(transform, camera, deltaTime);
		}
		else
		{
			PerspectiveUpdate(transform, deltaTime, deltaMousePos);
		}
	}

	void CameraController::OrthographicUpdate(
		TransformComponent& transform,
		Camera& camera,
		const float deltaTime
	)
	{

		if (Input::PressedKey(Key::D))
		{
			transform.position.x += movementSpeed * deltaTime;
		}
		else if (Input::PressedKey(Key::A))
		{
			transform.position.x -= movementSpeed * deltaTime;
		}

		if (Input::PressedKey(Key::W))
		{
			transform.position.y += movementSpeed * deltaTime;
		}
		else if (Input::PressedKey(Key::S))
		{
			transform.position.y -= movementSpeed * deltaTime;
		}

		if (Input::PressedKey(Key::Q))
		{
			float size = camera.GetOrthographicSize() + movementSpeed * deltaTime;
			
			camera.SetOrthographicSize(size);
		}
		else if (Input::PressedKey(Key::E))
		{
			float size = Math::Max(camera.GetOrthographicSize() - movementSpeed * deltaTime, 0.001f);
			
			camera.SetOrthographicSize(size);
		}
	}

	void CameraController::PerspectiveUpdate(
		TransformComponent& transform,
		const float deltaTime,
		glm::vec2 deltaMousePos
	)
	{
		glm::vec3 rightDirection = glm::rotate(transform.rotation, glm::vec3(1.f, 0.f, 0.f));
		glm::vec3 upDirection = glm::rotate(transform.rotation, glm::vec3(0.f, 1.f, 0.f));
		glm::vec3 forwardDirection = glm::rotate(transform.rotation, glm::vec3(0.f, 0.f, -1.f));

		if (Input::PressedKey(Key::D))
		{
			transform.position += rightDirection * movementSpeed * deltaTime;
		}
		else if (Input::PressedKey(Key::A))
		{
			transform.position -= rightDirection * movementSpeed * deltaTime;
		}

		if (Input::PressedKey(Key::E))
		{
			transform.position += upDirection * movementSpeed * deltaTime;
		}
		else if (Input::PressedKey(Key::Q))
		{
			transform.position -= upDirection * movementSpeed * deltaTime;
		}

		// * -1.f because Z is wrong way around
		if (Input::PressedKey(Key::W))
		{
			transform.position += forwardDirection * movementSpeed * deltaTime;
		}
		else if (Input::PressedKey(Key::S))
		{
			transform.position -= forwardDirection * movementSpeed * deltaTime;
		}

		_pitch += deltaMousePos.y * rotationSpeed * 0.05f;
		_yaw += Math::Sign(upDirection.y) * deltaMousePos.x * rotationSpeed * 0.05f;

		transform.rotation = glm::quat(glm::vec3(-_pitch, -_yaw, 0.f));
	}
}
