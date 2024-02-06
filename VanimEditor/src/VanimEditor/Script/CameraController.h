#pragma once

#include "VanimEditor/ECS/ScriptableEntity.h"
#include "VanimEditor/ECS/Components.h"

#include <iostream>

namespace Vanim
{
	class CameraController : public ScriptableEntity
	{
	public:
		// void Create() override;

		void Update(const double deltaTime) override;

		// void Destroy() override;
	public:
		float movementSpeed = 5.0f;
		float rotationSpeed = 0.5f;
	private:
		glm::vec2 _lastMousePos{ 0.0f };
	};
}
