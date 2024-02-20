#pragma once

#include "VanimCore.h"

namespace Vanim
{
	class IAnimation
	{
	public:
		// progress goes from 0 to 1
		virtual void Play(float progress) = 0;
	};
}
