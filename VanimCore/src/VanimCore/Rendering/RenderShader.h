#pragma once

#include "VanimCore/OpenGL/Shader.h"

namespace Vanim
{
	class RenderShader
	{
	public:
		RenderShader(
			const char* vertexPath,
			const char* fragmentPath
		);
		RenderShader(const Shared<Shader>& shader);

		const Shared<Shader>& GetShader() const { return _shader; }

		GLint GetViewProjectionID() const { return _viewProjectionID; }
		GLint GetModelMatrixID() const { return _modelMatrix; }
		GLint GetColorID() const { return _colorID; }
	private:
		Shared<Shader> _shader;

		GLint _viewProjectionID = -1;
		GLint _modelMatrix = -1;
		GLint _colorID = -1;
	};
}
