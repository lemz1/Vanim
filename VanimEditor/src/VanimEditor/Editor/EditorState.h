#pragma once

#include "VanimCore.h"

#include "VanimEditor/ECS/Scene.h"
#include "VanimEditor/Rendering/Panels/SceneHierarchyPanel.h"
#include "VanimEditor/Rendering/Renderer.h"

namespace Vanim
{
	class EditorState : public State
	{
	public:
		void Create() override;

		void Update(const double deltaTime) override;

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
