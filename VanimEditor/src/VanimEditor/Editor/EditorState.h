#pragma once

#include "VanimCore.h"

#include "VanimEditor/Rendering/Panels/SceneHierarchyPanel.h"
#include "VanimEditor/Rendering/Panels/AnimatorPanel.h"

#include "VanimEditor/Animation/AnimationManager.h"
#include "VanimEditor/Animation/Animation.h"

namespace Vanim
{
	class EditorState : public State
	{
	public:
		void Create() override;

		void Update(const float deltaTime) override;

		void Draw() override;

		void DrawImGui() override;

		void Destroy() override;
	private:
		Shared<Shader> _defaultShader;
		Unique<Animation> _createAnimation;

		Shared<AnimationManager> _animationManager;

		Scene _scene;
		Unique<SceneHierarchyPanel> _sceneHierarchyPanel;
		Unique<AnimatorPanel> _animatorPanel;

		Unique<FrameBuffer> _sceneFrameBuffer;
		Unique<Texture> _sceneTexture;
		Unique<RenderBuffer> _sceneDepthBuffer;

		bool _showDebugInfo = false;
	};
}
