#pragma once

#include "VanimCore/Base.h"

namespace Vanim
{
	struct Rect
	{
	public:
		Rect() = default;
		Rect(
			float left,
			float right,
			float bottom,
			float top
		)
		:	left(left),
			right(right),
			bottom(bottom),
			top(top)
		{}

		float left;
		float right;
		float bottom;
		float top;
	};
}
