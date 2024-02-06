#include "editorpch.h"
#include "CameraController.h"

#include "VanimCore.h"

namespace Vanim
{
	void CameraController::Update(const double deltaTime)
	{
		if (!HasAllOf<TransformComponent, CameraComponent>())
		{
			return;
		}


		glm::vec2 mousePos = Input::GetMousePosition();
		glm::vec2 deltaMousePos = mousePos - _lastMousePos;
		_lastMousePos = mousePos;

		auto [transform, camera] = GetComponents<TransformComponent, CameraComponent>();

	}
}
