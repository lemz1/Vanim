#pragma once

#include "VanimCore/Component/Transform.h"

namespace Vanim
{
	struct CameraSpecification
	{
		uint32_t	width;
		uint32_t	height;
		float		verticalFOV;
		float		nearClipPlane;
		float		farClipPlane;
		float		movementSpeed;
		float		rotationSpeed;
		float		orthographicSize;
		bool		isOrthographic;
	};

	struct Camera
	{
	public:
		Camera() = default;
		Camera(
			const Transform& transform,
			const CameraSpecification& spec
		);

	private:
		void RecalculateProjection();
		void RecalculateView();
	private:
		Transform	_transform;

		glm::mat4	_view;
		glm::mat4	_projection;
		glm::mat4	_viewProjection;

		uint32_t	_width;
		uint32_t	_height;
		float		_verticalFOV;
		float		_nearClipPlane;
		float		_farClipPlane;
		float		_movementSpeed;
		float		_rotationSpeed;
		float		_orthographicSize;
		bool		_isOrthographic;
	};
}
