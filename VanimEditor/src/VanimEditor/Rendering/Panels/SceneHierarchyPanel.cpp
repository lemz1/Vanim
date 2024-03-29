#include "editorpch.h"
#include "SceneHierarchyPanel.h"

#include <imgui.h>

#include "VanimEditor/Rendering/MyGui.h"

namespace Vanim
{
	SceneHierarchyPanel::SceneHierarchyPanel(Scene* context)
	:	_context(context)
	{}

	void SceneHierarchyPanel::DrawImGui()
	{
		ImGui::Begin("Scene Hierarchy", nullptr, MyGui::defaultWindowFlags);
		
		// i would have done _context->GetEntitiesOfType, however entt::entity makes 
		// it not work since it needs to then use size_hint which the template doesnt have
		// so im using GetEntitiesOfTypes instead
		for (auto& entity : _context->GetEntitiesOfTypes<entt::entity>())
		{
			DrawEntityNode(entity);
		}

		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity& entity)
	{
		const char* tag = "No Tag";
		if (entity.HasAnyOf<TagComponent>())
		{
			tag = entity.GetComponent<TagComponent>().tag;
		}

		bool selected = ImGui::Selectable(tag, _selectionContext == entity);
		
		if (selected)
		{
			_selectionContext = entity;
		}
	}
}
