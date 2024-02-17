#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <type_traits>

#define Arithmetic typename std::enable_if<std::is_arithmetic<T>::value, T>::type

namespace Vanim
{
	class Math
	{
	public:
		template<typename T>
		static Arithmetic Sign(T a)
		{
			return a < (T)0 ? (T)-1 : (T)1;
		}

		template<typename T>
		static Arithmetic Abs(T a)
		{
			return a < (T)0 ? -a : a;
		}

		template<typename T>
		static Arithmetic Max(T a, T b)
		{
			return a > b ? a : b;
		}

		template<typename T>
		static Arithmetic Min(T a, T b)
		{
			return a < b ? a : b;
		}

		// value should be a floating point
		template<typename T>
		static Arithmetic Pow(T value, int32_t exponent)
		{
			T result = 1;
			
			if (exponent < 0)
			{
				for (int32_t i = 0; i > exponent; i--)
				{
					result /= value;
				}
			} 
			else 
			{
				for (int32_t i = 0; i < exponent; i++)
				{
					result *= value;
				}
			}

			return result;
		}

		static glm::vec3 QuaternionInRadians(const glm::quat& quaternion)
		{
			return glm::axis(quaternion) * glm::angle(quaternion);
		}

		static glm::vec3 QuaternionInDegrees(const glm::quat& quaternion)
		{
			return glm::axis(quaternion) * glm::angle(quaternion) * (float)(toDegrees);
		}
	public:
		static constexpr double pi = 3.1415926;
		static constexpr double toDegrees = 180.0 / pi;
		static constexpr double toRadians = pi / 180.0;
	};
}
