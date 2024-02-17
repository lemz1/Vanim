#pragma once

#include "VanimCore.h"

#include "VanimCore/Rendering/Graph2D.h"

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
		Scene _scene;
		SceneHierarchyPanel _sceneHierarchyPanel;

		Unique<Renderer> _renderer;
		Unique<FrameBuffer> _sceneFrameBuffer;
		Unique<Texture> _sceneTexture;
	};
}
