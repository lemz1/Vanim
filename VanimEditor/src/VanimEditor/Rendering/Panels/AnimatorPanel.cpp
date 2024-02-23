#include "editorpch.h"
#include "AnimatorPanel.h"

#include <imgui.h>

#include "VanimEditor/Rendering/MyGui.h"

namespace Vanim
{
	AnimatorPanel::AnimatorPanel(
		Scene* context, 
		AnimationManager* animationManager
	)
	:	_context(context),
		_animationManager(animationManager)
	{}

	void AnimatorPanel::DrawImGui()
	{
		ImGui::Begin("Animator", nullptr, MyGui::defaultWindowFlags);

		auto& style = ImGui::GetStyle();

		ImVec2 contentRegionAvail = ImGui::GetContentRegionAvail();

		// 20 pixels per seconds
		float sliderWidth = 20 * _animationManager->totalTimeSeconds;

		ImVec2 sliderPos = ImGui::GetCursorPos();
		ImGui::PushItemWidth(sliderWidth);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // make text invisible
		ImGui::SliderFloat("##Animation Time", &_animationManager->time, 0, _animationManager->totalTimeSeconds);
		ImGui::PopStyleColor();

		ImVec2 plusSymbolPos = ImGui::GetCursorPos();

		uint32_t minutes = Math::Floor(_animationManager->time / 60.0f);
		uint32_t seconds = (uint32_t)Math::Floor(_animationManager->time) % 60;
		uint32_t ms = Math::Floor((_animationManager->time - Math::Floor(_animationManager->time)) * 100);

		const char* extraZeroSeconds = seconds < 10 ? "0" : "";
		const char* extraZeroMS = ms < 10 ? "0" : "";

		std::string valueText = std::to_string(minutes) + ":" 
							  + extraZeroSeconds + std::to_string(seconds) + ":"
							  + extraZeroMS + std::to_string(ms);

		float textWidth = ImGui::CalcTextSize(valueText.c_str()).x;

		ImGui::SetCursorPosX(sliderPos.x + (contentRegionAvail.x - textWidth) / 2.0f + ImGui::GetScrollX());
		ImGui::SetCursorPosY(sliderPos.y + style.FramePadding.y);
		ImGui::Text(valueText.c_str());

		for (size_t i = 0; i < _animationManager->animations; i++)
		{
			ImGui::Text("Animation");
		}

		ImGui::SetCursorPosX(plusSymbolPos.x + ImGui::GetScrollX());
		ImGui::SetCursorPosY(plusSymbolPos.y);
		if (ImGui::Button("+", ImVec2(25, 25)))
		{
			_animationManager->animations++;
		}

		if (Input::PressedMouseButton(MouseButton::ButtonLeft))
		{
			float windowX = ImGui::GetWindowPos().x;
			float mouseX = Input::GetMousePosition().x;

			constexpr float threshold = 25.0f;
			constexpr float speed = 0.1f;

			// check mouse being more left than window
			float deltaX = Math::Min(mouseX - windowX - threshold, 0.0f);

			// check mouse being more right than window
			if (deltaX == 0) 
			{
				deltaX = Math::Max(mouseX - (windowX + ImGui::GetWindowWidth()) + threshold, 0.0f);
			}

			float scrollX = ImGui::GetScrollX() + deltaX * speed;

			ImGui::SetScrollX(scrollX);
		}

		ImGui::End();
	}
}
