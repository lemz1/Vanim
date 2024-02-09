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
		void Resize(
			uint32_t width, 
			uint32_t height
		);

		float GetVerticalFOV() const { return _verticalFOV; }
		void SetVerticalFOV(float verticalFOV) { _verticalFOV = verticalFOV; RecalculateProjection(); }

		float GetNearClipPlane() const { return _nearClipPlane; }
		void SetNearClipPlane(float nearClipPlane) { _nearClipPlane = nearClipPlane; RecalculateProjection(); }
		
		float GetFarClipPlane() const { return _farClipPlane; }
		void SetFarClipPlane(float farClipPlane) { _farClipPlane = farClipPlane; RecalculateProjection(); }
		
		float GetOrthographicSize() const { return _orthographicSize; }
		void SetOrthographicSize(float orthographicSize) { _orthographicSize = orthographicSize; RecalculateProjection(); }

		bool IsOrthographic() const { return _isOrthographic; }
		void SetOrthographic(float isOrthographic) { _isOrthographic = isOrthographic; RecalculateProjection(); }

		const glm::mat4& GetProjection() const { return _projection; }
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
