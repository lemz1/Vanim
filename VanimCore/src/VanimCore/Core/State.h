#pragma once

namespace Vanim
{
	class State
	{
	public:
		State() = default;
		virtual ~State() = default;
		
		virtual void Create() {}

		virtual void Update(const double deltaTime) {}

		virtual void Draw() {}

		virtual void DrawImGui() {}

		virtual void Event() {}

		virtual void Destroy() {}
	};
}
