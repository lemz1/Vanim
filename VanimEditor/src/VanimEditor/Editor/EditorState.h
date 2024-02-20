#pragma once

#include "VanimCore.h"

#include "VanimEditor/Rendering/Panels/SceneHierarchyPanel.h"

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
		Shared<Shader> _animationShader;

		Scene _scene;
		SceneHierarchyPanel _sceneHierarchyPanel;

		Unique<FrameBuffer> _sceneFrameBuffer;
		Unique<Texture> _sceneTexture;
		Unique<RenderBuffer> _sceneDepthBuffer;

		bool _showDebugInfo = false;
	};
}
