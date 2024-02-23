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
		static Arithmetic Clamp(T a, T b, T value)
		{
			return value < a ? a :
				   value > b ? b :
				   value;
		}

		template<typename T>
		static Arithmetic Sign(T value)
		{
			return value < (T)0 ? (T)-1 : (T)1;
		}

		template<typename T>
		static Arithmetic Abs(T value)
		{
			return value < (T)0 ? -value : value;
		}

		template<typename T>
		static Arithmetic Ceil(T value)
		{
			return (T)ceil(value);
		}

		template<typename T>
		static Arithmetic Floor(T value)
		{
			return (T)floor(value);
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

		template<typename T>
		static Arithmetic Sin(T radians)
		{
			return (T)sin(radians);
		}

		template<typename T>
		static Arithmetic Cos(T radians)
		{
			return (T)cos(radians);
		}

		template<typename T>
		static Arithmetic Tan(T radians)
		{
			return (T)tan(radians);
		}

		template<typename T>
		static Arithmetic Atan(T radians)
		{
			return (T)atan(radians);
		}

		template<typename T>
		static Arithmetic Atan2(T x, T y)
		{
			return (T)atan2(x, y);
		}

		// values should be floating point
		template<typename T>
		static Arithmetic Lerp(T a, T b, T t)
		{
			return a + ((b - a) * t);
		}

		// values should be floating point
		template<typename T>
		static Arithmetic InverseLerp(T a, T b, T value)
		{
			if (a == b)
			{
				return (T)0;
			}

			return (value - a) / (b - a);
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
