#pragma once

#include "VanimCore.h"

namespace Vanim
{
	class Animation
	{
	public:
		Animation(
			const char* fragmentPath,
			std::vector<Entity>& entities
		);

		// progress goes from 0 to 1
		void Play(float progress);
	private:
		Shared<Shader>	_shader;
		GLint _viewProjectionID = -1;
		GLint _modelMatrixID = -1;
		GLint _progressID = -1;
		GLint _colorID = -1;
	};
}
