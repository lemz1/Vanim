#include "editorpch.h"
#include "MyGui.h"

namespace Vanim
{
	ImFont* MyGui::defaultFont = nullptr;
	ImFont* MyGui::boldFont = nullptr;

	void MyGui::SetImGuiStyle()
	{
		auto& io = ImGui::GetIO();

		auto& fonts = io.Fonts;
		defaultFont = io.FontDefault = fonts->AddFontFromFileTTF("Assets/Fonts/Roboto/Roboto-Regular.ttf", 18.0f);
		boldFont = fonts->AddFontFromFileTTF("Assets/Fonts/Roboto/Roboto-Bold.ttf", 18.0f);

		auto& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
	}
}
