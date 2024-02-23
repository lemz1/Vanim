#pragma once

#include "VanimCore.h"

#include "VanimEditor/Animation/AnimationManager.h"

namespace Vanim
{
	class AnimatorPanel
	{
	public:
		AnimatorPanel() = default;
		AnimatorPanel(
			Scene* context, 
			AnimationManager* animationManager
		);

		void DrawImGui();
	private:
		Scene* _context;
		AnimationManager* _animationManager;

		Entity _selectionContext;
	};
}
