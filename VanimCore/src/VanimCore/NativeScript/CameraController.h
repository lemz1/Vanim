#pragma once

#include "VanimCore/ScriptableEntity.h"
#include "VanimCore/Components.h"

#include <iostream>

namespace Vanim
{
	class CameraController : public ScriptableEntity
	{
	public:
		void Create() {}

		void Update(const double deltaTime);

		void Destroy() {}
	public:
		float movementSpeed = 5.0f;
		float rotationSpeed = 0.5f;
	};
}
