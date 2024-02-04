#include "vanimpch.h"
#include "CameraController.h"

namespace Vanim
{
	void CameraController::Update(const double deltaTime)
	{
		if (!HasAllOf<TransformComponent, CameraComponent>())
		{
			return;
		}

		auto& transform = GetComponent<TransformComponent>().transform;
		auto& camera = GetComponent<CameraComponent>().camera;

		std::cout << "Updating Camera" << std::endl;
	}
}
