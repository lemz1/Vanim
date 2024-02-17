#pragma once

#include "VanimCore/Base.h"

namespace Vanim
{
	class Ease
	{
	public:
		static float InQuad(float t)
		{
			return t * t;
		}

		static float OutQuad(float t)
		{
			return 1.f - (1.f - t) * (1.f - t);
		}

		static float InOutQuad(float t)
		{
			return t < 0.5f ? 2.f * t * t : 1.f - pow(-2.f * t + 2.f, 2.f) / 2.f;
		}

		static float InCubic(float t)
		{
			return t * t * t;
		}

		static float OutCubic(float t)
		{
			return 1.f - pow(1.f - t, 3.f);
		}

		static float InOutCubic(float t)
		{
			return t < 0.5f ? 4.f * t * t * t : 1.f - pow(-2.f * t + 2.f, 3.f) / 2.f;
		}

		static float InQuart(float t)
		{
			return t * t * t * t;
		}

		static float OutQuart(float t)
		{
			return 1.f - pow(1.f - t, 4.f);
		}

		static float InOutQuart(float t)
		{
			return t < 0.5f ? 8.f * t * t * t * t : 1.f - pow(-2.f * t + 2.f, 4.f) / 2.f;
		}

		static float InQuint(float t)
		{
			return t * t * t * t * t;
		}

		static float OutQuint(float t)
		{
			return 1.f - pow(1.f - t, 5.f);
		}

		static float InOutQuint(float t)
		{
			return t < 0.5f ? 16.f * t * t * t * t * t : 1.f - pow(-2.f * t + 2.f, 5.f) / 2.f;
		}

		static float InExpo(float t)
		{
			return t == 0.f ? 0.f : pow(2.f, 10.f * t - 10.f);
		}

		static float OutExpo(float t)
		{
			return t == 1.f ? 1.f : 1.f - pow(2.f, -10.f * t);
		}

		static float InOutExpo(float t)
		{
			return t == 0.f
				? 0.f
				: t == 1.f
				? 1.f
				: t < 0.5f ? pow(2.f, 20.f * t - 10.f) / 2.f
				: (2.f - pow(2.f, -20.f * t + 10.f)) / 2.f;
		}

		static float InCirc(float t)
		{
			return 1.f - sqrt(1.f - pow(t, 2.f));
		}

		static float OutCirc(float t)
		{
			return sqrt(1.f - pow(t - 1.f, 2.f));
		}

		static float InOutCirc(float t)
		{
			return t < 0.5f
				? (1.f - sqrt(1.f - pow(2.f * t, 2.f))) / 2.f
				: (sqrt(1.f - pow(-2.f * t + 2.f, 2.f)) + 1.f) / 2.f;
		}

		static float InBack(float t)
		{
			constexpr float c1 = 1.70158f;
			constexpr float c2 = c1 + 1.f;

			return c2 * t * t * t - c1 * t * t;
		}

		static float OutBack(float t)
		{
			constexpr float c1 = 1.70158f;
			constexpr float c2 = c1 + 1.f;

			return 1.f + c2 * pow(t - 1.f, 3.f) + c1 * pow(t - 1.f, 2.f);
		}

		static float InOutBack(float t)
		{
			constexpr float c1 = 1.70158f;
			constexpr float c2 = c1 * 1.525f;

			return t < 0.5f
				? (pow(2.f * t, 2.f) * ((c2 + 1.f) * 2.f * t - c2)) / 2.f
				: (pow(2.f * t - 2.f, 2.f) * ((c2 + 1.f) * (t * 2.f - 2.f) + c2) + 2.f) / 2.f;
		}

		static float InElastic(float t)
		{
			constexpr float PI = 3.1415926f;
			constexpr float c = (2.f * PI) / 3.f;

			return t == 0.f
				? 0.f
				: t == 1.f
				? 1.f
				: -pow(2.f, 10.f * t - 10.f) * sin((t * 10.f - 10.75f) * c);
		}

		static float OutElastic(float t)
		{
			constexpr float PI = 3.1415926f;
			constexpr float c = (2.f * PI) / 3.f;

			return t == 0.f
				? 0.f
				: t == 1.f
				? 1.f
				: pow(2.f, -10.f * t) * sin((t * 10.f - 0.75f) * c) + 1.f;
		}

		static float InOutElastic(float t)
		{
			constexpr float PI = 3.1415926f;
			constexpr float c = (2.f * PI) / 4.5f;

			return t == 0.f
				? 0.f
				: t == 1.f
				? 1.f
				: t < 0.5f
				? -(pow(2.f, 20.f * t - 10.f) * sin((20.f * t - 11.125f) * c)) / 2.f
				: (pow(2.f, -20.f * t + 10.f) * sin((20.f * t - 11.125f) * c)) / 2.f + 1.f;
		}

		static float InBounce(float t)
		{
			return 1.f - OutBounce(1.f - t);
		}

		static float OutBounce(float t)
		{
			constexpr float n = 7.5625f;
			constexpr float d = 2.75f;

			if (t < 1.f / d)
			{
				return n * t * t;
			}
			else if (t < 2.f / d)
			{
				t -= 1.5f / d;
				return n * t * t + 0.75f;
			}
			else if (t < 2.5f / d)
			{
				t -= 2.25f / d;
				return n * t * t + 0.9375f;
			}
			else
			{
				t -= 2.625f / d;
				return n * t * t + 0.984375f;
			}
		}

		static float InOutBounce(float t)
		{
			return t < 0.5f
				? (1.f - OutBounce(1.f - 2.f * t)) / 2.f
				: (1.f + OutBounce(2.f * t - 1.f)) / 2.f;
		}

		static float InSine(float t)
		{
			constexpr float PI = 3.1415926f;

			return 1.f - cos((t * PI) / 2.f);
		}
		
		static float OutSine(float t)
		{
			constexpr float PI = 3.1415926f;

			return sin((t * PI) / 2.f);
		}

		static float InOutSine(float t)
		{
			constexpr float PI = 3.1415926f;

			return -(cos(PI * t) - 1.f) / 2.f;
		}
	};
}
