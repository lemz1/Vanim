#pragma once

#include "VanimCore/ECS/Entity.h"
#include "VanimCore/ECS/Scene.h"

namespace Vanim
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(Scene* context);

		void SetContext(Scene* context);
		
		void DrawImGui();
	private:
		void DrawEntityNode(Entity& entity);
	private:
		Scene* _context;
		Entity _selectionContext;
	};
}
