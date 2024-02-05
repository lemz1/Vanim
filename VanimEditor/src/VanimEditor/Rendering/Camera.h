#pragma once

#include <glm/glm.hpp>

namespace Vanim
{
	struct CameraSpecification
	{
		uint32_t	width = 1280;
		uint32_t	height = 720;
		float		verticalFOV = 45.0f;
		float		nearClipPlane = 0.1f;
		float		farClipPlane = 100.0f;
		float		orthographicSize = 5.0f;
		bool		isOrthographic = true;
	};

	class Camera
	{
	public:
		Camera(const CameraSpecification& spec = {});

		uint32_t GetWidth() const { return _width; }
		uint32_t GetHeight() const { return _height; }

		float GetVerticalFOV() const { return _verticalFOV; }
		float GetNearClipPlane() const { return _nearClipPlane; }
		float GetFarClipPlane() const { return _farClipPlane; }
		float GetOrthographicSize() const { return _orthographicSize; }

		bool IsOrthographic() const { return _isOrthographic; }
	private:
		void RecalculateProjection();
	private:
		glm::mat4	_projection = glm::mat4(1.f);
					
		uint32_t	_width;
		uint32_t	_height;
		float		_verticalFOV;
		float		_nearClipPlane;
		float		_farClipPlane;
		float		_orthographicSize;
		bool		_isOrthographic;
	};
}
