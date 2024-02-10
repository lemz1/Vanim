#pragma once

#include "VanimCore.h"

#include <iostream>

namespace Vanim
{
	class CameraController : public ScriptableEntity
	{
	public:
		// void Create() override;

		void Update(const float deltaTime) override;

		// void Destroy() override;
	private:
		void OrthographicUpdate(
			TransformComponent& transform,
			Camera& camera,
			const float deltaTime
		);
		void PerspectiveUpdate(
			TransformComponent& transform,
			const float deltaTime, 
			glm::vec2 deltaMousePos
		);
	public:
		float movementSpeed = 5.0f;
		float rotationSpeed = 0.05f;
	private:
		glm::vec2 _lastMousePos{ 0.0f };

		float _pitch = 0.f;
		float _yaw = 0.f;
	};
}
