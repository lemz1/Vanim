#pragma once

#include "VanimCore/Base.h"

#include <glm/glm.hpp>

namespace Vanim
{
	class Color
	{
	public:
		static glm::vec3 RGBtoHSB(const glm::vec4& rgb);

		static glm::vec4 HSBtoRGB(const glm::vec3& hsb);

		static glm::vec3 RGBtoHSL(const glm::vec4& rgb);

		static glm::vec4 HSLtoRGB(const glm::vec3& hsl);
	public:
		static constexpr glm::vec4 white		{ 1.00f, 1.00f, 1.00f, 1.00f };
		static constexpr glm::vec4 black		{ 0.00f, 0.00f, 0.00f, 1.00f };

		static constexpr glm::vec4 red1			{ 0.20f, 0.00f, 0.00f, 1.00f };
		static constexpr glm::vec4 red2			{ 0.40f, 0.00f, 0.00f, 1.00f };
		static constexpr glm::vec4 red3			{ 0.60f, 0.00f, 0.00f, 1.00f };
		static constexpr glm::vec4 red4			{ 0.80f, 0.00f, 0.00f, 1.00f };
		static constexpr glm::vec4 red5			{ 1.00f, 0.00f, 0.00f, 1.00f };
		static constexpr glm::vec4 red6			{ 1.00f, 0.20f, 0.20f, 1.00f };
		static constexpr glm::vec4 red7			{ 1.00f, 0.40f, 0.40f, 1.00f };
		static constexpr glm::vec4 red8			{ 1.00f, 0.60f, 0.60f, 1.00f };
		static constexpr glm::vec4 red9			{ 1.00f, 0.80f, 0.80f, 1.00f };

		static constexpr glm::vec4 green1		{ 0.00f, 0.20f, 0.00f, 1.00f };
		static constexpr glm::vec4 green2		{ 0.00f, 0.40f, 0.00f, 1.00f };
		static constexpr glm::vec4 green3		{ 0.00f, 0.60f, 0.00f, 1.00f };
		static constexpr glm::vec4 green4		{ 0.00f, 0.80f, 0.00f, 1.00f };
		static constexpr glm::vec4 green5		{ 0.00f, 1.00f, 0.00f, 1.00f };
		static constexpr glm::vec4 green6		{ 0.20f, 1.00f, 0.20f, 1.00f };
		static constexpr glm::vec4 green7		{ 0.40f, 1.00f, 0.40f, 1.00f };
		static constexpr glm::vec4 green8		{ 0.60f, 1.00f, 0.60f, 1.00f };
		static constexpr glm::vec4 green9		{ 0.80f, 1.00f, 0.80f, 1.00f };

		static constexpr glm::vec4 blue1		{ 0.00f, 0.20f, 0.00f, 1.00f };
		static constexpr glm::vec4 blue2		{ 0.00f, 0.40f, 0.00f, 1.00f };
		static constexpr glm::vec4 blue3		{ 0.00f, 0.60f, 0.00f, 1.00f };
		static constexpr glm::vec4 blue4		{ 0.00f, 0.80f, 0.00f, 1.00f };
		static constexpr glm::vec4 blue5		{ 0.00f, 1.00f, 0.00f, 1.00f };
		static constexpr glm::vec4 blue6		{ 0.20f, 1.00f, 0.20f, 1.00f };
		static constexpr glm::vec4 blue7		{ 0.40f, 1.00f, 0.40f, 1.00f };
		static constexpr glm::vec4 blue8		{ 0.60f, 1.00f, 0.60f, 1.00f };
		static constexpr glm::vec4 blue9		{ 0.80f, 1.00f, 0.80f, 1.00f };

		static constexpr glm::vec4 yellow1		{ 0.20f, 0.20f, 0.00f, 1.00f };
		static constexpr glm::vec4 yellow2		{ 0.40f, 0.40f, 0.00f, 1.00f };
		static constexpr glm::vec4 yellow3		{ 0.60f, 0.60f, 0.00f, 1.00f };
		static constexpr glm::vec4 yellow4		{ 0.80f, 0.80f, 0.00f, 1.00f };
		static constexpr glm::vec4 yellow5		{ 1.00f, 1.00f, 0.00f, 1.00f };
		static constexpr glm::vec4 yellow6		{ 1.00f, 1.00f, 0.20f, 1.00f };
		static constexpr glm::vec4 yellow7		{ 1.00f, 1.00f, 0.40f, 1.00f };
		static constexpr glm::vec4 yellow8		{ 1.00f, 1.00f, 0.60f, 1.00f };
		static constexpr glm::vec4 yellow9		{ 1.00f, 1.00f, 0.80f, 1.00f };

		static constexpr glm::vec4 cyan1		{ 0.00f, 0.20f, 0.20f, 1.00f };
		static constexpr glm::vec4 cyan2		{ 0.00f, 0.40f, 0.40f, 1.00f };
		static constexpr glm::vec4 cyan3		{ 0.00f, 0.60f, 0.60f, 1.00f };
		static constexpr glm::vec4 cyan4		{ 0.00f, 0.80f, 0.80f, 1.00f };
		static constexpr glm::vec4 cyan5		{ 0.00f, 1.00f, 1.00f, 1.00f };
		static constexpr glm::vec4 cyan6		{ 0.20f, 1.00f, 1.00f, 1.00f };
		static constexpr glm::vec4 cyan7		{ 0.40f, 1.00f, 1.00f, 1.00f };
		static constexpr glm::vec4 cyan8		{ 0.60f, 1.00f, 1.00f, 1.00f };
		static constexpr glm::vec4 cyan9		{ 0.80f, 1.00f, 1.00f, 1.00f };

		static constexpr glm::vec4 purple1		{ 0.20f, 0.00f, 0.20f, 1.00f };
		static constexpr glm::vec4 purple2		{ 0.40f, 0.00f, 0.40f, 1.00f };
		static constexpr glm::vec4 purple3		{ 0.60f, 0.00f, 0.60f, 1.00f };
		static constexpr glm::vec4 purple4		{ 0.80f, 0.00f, 0.80f, 1.00f };
		static constexpr glm::vec4 purple5		{ 1.00f, 0.00f, 1.00f, 1.00f };
		static constexpr glm::vec4 purple6		{ 1.00f, 0.20f, 1.00f, 1.00f };
		static constexpr glm::vec4 purple7		{ 1.00f, 0.40f, 1.00f, 1.00f };
		static constexpr glm::vec4 purple8		{ 1.00f, 0.60f, 1.00f, 1.00f };
		static constexpr glm::vec4 purple9		{ 1.00f, 0.80f, 1.00f, 1.00f };
	};
}
