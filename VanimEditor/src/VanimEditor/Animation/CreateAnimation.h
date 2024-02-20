#pragma once

#include "VanimEditor/Animation/IAnimation.h"

namespace Vanim
{
	class CreateAnimation : IAnimation
	{
	public:
		CreateAnimation(std::vector<Entity>& entities);

		void Play(float progress) override;
	private:
		std::vector<Entity> _entities;
		Shared<AnimationShader> _animationShader;
	};
}
