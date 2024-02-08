#include "editorpch.h"
#include "Camera.h"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Vanim
{
	Camera::Camera(const CameraSpecification& spec)
	:	_width(spec.width),
		_height(spec.height),
		_verticalFOV(spec.verticalFOV),
		_nearClipPlane(spec.nearClipPlane),
		_farClipPlane(spec.farClipPlane),
		_orthographicSize(spec.orthographicSize),
		_isOrthographic(spec.isOrthographic)
	{
		RecalculateProjection();
	}

	void Camera::Resize(
		uint32_t width, 
		uint32_t height
	)
	{
		if (_width == width && _height == height)
		{
			return;
		}

		_width = width;
		_height = height;

		RecalculateProjection();
	}

	void Camera::RecalculateProjection()
	{
		if (_isOrthographic)
		{
			float aspect = (float)_width / (float)_height;

			_projection = glm::ortho(
				aspect * _orthographicSize * -0.5f,
				aspect * _orthographicSize * 0.5f,
				_orthographicSize * -0.5f,
				_orthographicSize * 0.5f,
				_nearClipPlane,
				_farClipPlane
			);
		}
		else
		{
			_projection = glm::perspectiveFov(
				glm::radians(_verticalFOV),
				(float)_width,
				(float)_height,
				_nearClipPlane,
				_farClipPlane
			);
		}
	}
}
