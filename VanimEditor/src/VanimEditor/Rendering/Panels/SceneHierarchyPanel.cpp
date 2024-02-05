#include "editorpch.h"
#include "SceneHierarchyPanel.h"

#include <imgui.h>

namespace Vanim
{
	SceneHierarchyPanel::SceneHierarchyPanel(Scene* context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(Scene* context)
	{
		_context = context;
	}

	void SceneHierarchyPanel::DrawImGui()
	{
		ImGui::Begin("Scene Hierarchy");

		for (auto& entity : _context->GetEntitiesOfType<entt::entity>())
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
