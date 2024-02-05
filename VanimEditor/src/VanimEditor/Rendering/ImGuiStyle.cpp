#include "editorpch.h"
#include "ImGuiStyle.h"

namespace Vanim
{
	void ImGuiStyle::SetImGuiStyle()
	{
		auto& style = ImGui::GetStyle();

		style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
	}
}
