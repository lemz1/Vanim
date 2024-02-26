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
		Shared<RenderShader> _shader;
		GLint _progressID = -1;
	};
}
