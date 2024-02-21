#include "corepch.h"
#include "Color.h"

namespace Vanim
{
	glm::vec3 Color::RGBtoHSB(const glm::vec4& rgb)
	{
		glm::vec3 hsb{ 0.0f };
		float r = rgb.r;
		float g = rgb.g;
		float b = rgb.b;

		float maxChannel = std::max({ r, g, b });
		float minChannel = std::min({ r, g, b });

		hsb.z = maxChannel; // Brightness

		float delta = maxChannel - minChannel;

		if (maxChannel == minChannel)
		{
			hsb.x = 0.0f; // Hue
			hsb.y = 0.0f; // Saturation
		}
		else
		{
			if (maxChannel == r)
			{
				hsb.x = 60.0f * fmod((g - b) / delta, 6.0f);
			}
			else if (maxChannel == g)
			{
				hsb.x = 60.0f * ((b - r) / delta + 2.0f);
			}
			else
			{
				hsb.x = 60.0f * ((r - g) / delta + 4.0f);
			}

			hsb.y = delta / maxChannel; // Saturation
		}

		return hsb;
	}

	glm::vec4 Color::HSBtoRGB(const glm::vec3& hsb)
	{
		float h = hsb.x;
		float s = hsb.y;
		float v = hsb.z;

		float c = v * s;
		float x = c * (1.0f - std::abs(fmod(h / 60.0f, 2.0f) - 1.0f));
		float m = v - c;

		float r, g, b;
		if (h < 60.0f)
		{
			r = c; g = x; b = 0;
		}
		else if (h < 120.0f)
		{
			r = x; g = c; b = 0;
		}
		else if (h < 180.0f)
		{
			r = 0; g = c; b = x;
		}
		else if (h < 240.0f)
		{
			r = 0; g = x; b = c;
		}
		else if (h < 300.0f)
		{
			r = x; g = 0; b = c;
		}
		else
		{
			r = c; g = 0; b = x;
		}

		r += m; g += m; b += m;

		return glm::vec4(r, g, b, 1.0f);
	}

	glm::vec3 Color::RGBtoHSL(const glm::vec4& rgb)
	{
		glm::vec3 hsl{ 0.0f };
		float r = rgb.r;
		float g = rgb.g;
		float b = rgb.b;

		float maxChannel = std::max({ r, g, b });
		float minChannel = std::min({ r, g, b });

		hsl.z = (maxChannel + minChannel) / 2.0f; // Lightness

		if (maxChannel == minChannel)
		{
			hsl.x = 0.0f; // Hue
			hsl.y = 0.0f; // Saturation
		}
		else
		{
			float delta = maxChannel - minChannel;

			if (hsl.z < 0.5f)
			{
				hsl.y = delta / (maxChannel + minChannel);
			}
			else
			{
				hsl.y = delta / (2.0f - maxChannel - minChannel);
			}

			if (maxChannel == r)
			{
				hsl.x = (g - b) / delta + (g < b ? 6.0f : 0.0f);
			}
			else if (maxChannel == g)
			{
				hsl.x = (b - r) / delta + 2.0f;
			}
			else
			{
				hsl.x = (r - g) / delta + 4.0f;
			}

			hsl.x /= 6.0f;
		}

		return hsl;
	}

	glm::vec4 Color::HSLtoRGB(const glm::vec3& hsl)
	{
		float h = hsl.x;
		float s = hsl.y;
		float l = hsl.z;

		float c = (1.0f - std::abs(2.0f * l - 1.0f)) * s;
		float x = c * (1.0f - std::abs(fmod(h * 6.0f, 2.0f) - 1.0f));
		float m = l - c / 2.0f;

		float r, g, b;
		if (h < 1.0f / 6.0f)
		{
			r = c; g = x; b = 0;
		}
		else if (h < 1.0f / 3.0f)
		{
			r = x; g = c; b = 0;
		}
		else if (h < 0.5f)
		{
			r = 0; g = c; b = x;
		}
		else if (h < 2.0f / 3.0f)
		{
			r = 0; g = x; b = c;
		}
		else if (h < 5.0f / 6.0f)
		{
			r = x; g = 0; b = c;
		}
		else
		{
			r = c; g = 0; b = x;
		}

		r = r + m; g = g + m; b = b + m;

		return glm::vec4(r, g, b, 1.0f);
	}
}
