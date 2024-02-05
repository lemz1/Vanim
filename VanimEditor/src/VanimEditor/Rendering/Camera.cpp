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

	void Camera::RecalculateProjection()
	{
		if (_isOrthographic)
		{
			float aspect = (float)_width / (float)_height;

			// 2.f * _nearClipPlane because objects else need to have a relative z position of atleast _nearClipPlane * 0.5f which is weird
			// _orthographicSize * 0.5f because else the size is in 10 in total and not 5 in total
			_projection = glm::ortho(
				-aspect * _orthographicSize * 0.5f,
				aspect * _orthographicSize * 0.5f,
				-1.f * _orthographicSize * 0.5f,
				1.f * _orthographicSize * 0.5f,
				2.f * _nearClipPlane - _farClipPlane,
				_farClipPlane
			);
		}
		else
		{
			// 0.5f * _nearClipPlane because objects else need to have a relative z position of atleast _nearClipPlane * 2 which is weird
			_projection = glm::perspectiveFov(
				glm::radians(_verticalFOV),
				(float)_width,
				(float)_height,
				0.5f * _nearClipPlane,
				_farClipPlane
			);
		}
	}
}
