#pragma once

#include "VanimCore/Base.h"

#include "VanimCore/OpenGL/Shader.h"

#include <glm/glm.hpp>

namespace Vanim
{
	class AnimationShader
	{
	public:
		AnimationShader() = default;
		AnimationShader(const Shared<Shader>& shader);

		const Shared<Shader>& GetShader() const { return _shader; }
		
		void SetViewProjection(const glm::mat4 viewProjection);
		void SetViewProjection(
			const glm::mat4& view,
			const glm::mat4& projection
		);

		void SetModelMatrix(const glm::mat4& modelMatrix);

		void SetColor(const glm::vec4& color);

		operator const Shared<Shader>&() const { return _shader; }
	private:
		Shared<Shader>	_shader;
		GLint			_viewProjectionID;
		GLint			_modelMatrixID;
		GLint			_colorID;
	};
}
