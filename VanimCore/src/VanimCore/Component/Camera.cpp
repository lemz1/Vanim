#include "vanimpch.h"
#include "Camera.h"

namespace Vanim
{
	Camera::Camera(
		const Transform& transform, 
		const CameraSpecification& spec
	)
		: _transform(transform),
		_width(spec.width),
		_height(spec.height),
		_verticalFOV(spec.verticalFOV),
		_nearClipPlane(spec.nearClipPlane),
		_farClipPlane(spec.farClipPlane),
		_movementSpeed(spec.movementSpeed),
		_rotationSpeed(spec.rotationSpeed),
		_orthographicSize(spec.orthographicSize),
		_isOrthographic(spec.isOrthographic)
	{
		RecalculateProjection();
		RecalculateView();
	}

	void Camera::RecalculateProjection()
	{
		glm::mat4 translation = glm::translate(glm::mat4(1.f), _transform.GetPosition());
		glm::mat4 rotation = glm::mat4_cast(_transform.GetRotation());

		_view = translation * rotation;

		_viewProjection = _view * _projection;
	}

	void Camera::RecalculateView()
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

		_viewProjection = _view * _projection;
	}
}
