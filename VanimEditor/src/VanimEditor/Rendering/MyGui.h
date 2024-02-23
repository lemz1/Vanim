#pragma once

#include "VanimCore.h"

#include <imgui.h>

namespace Vanim
{
	class MyGui
	{
	public:
		static void SetImGuiStyle();

	public:
		#ifndef VANIM_DEBUG
		static constexpr int32_t defaultWindowFlags = ImGuiWindowFlags_NoCollapse;
		#else
		static constexpr int32_t defaultWindowFlags = ImGuiWindowFlags_None;
		#endif

		static ImFont* defaultFont;
		static ImFont* boldFont;
	};
}
