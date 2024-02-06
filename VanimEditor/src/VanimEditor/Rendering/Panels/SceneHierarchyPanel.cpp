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

		// i would have done _context->GetEntitiesOfType, however entt::entity makes 
		// it not work since it needs to then use size_hint which the template doesnt have
		for (auto entity : _context->_registry.view<entt::entity>())
		{
			DrawEntityNode(Entity(entity, &_context->_registry));
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
