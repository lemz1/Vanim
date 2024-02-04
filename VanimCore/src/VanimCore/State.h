#pragma once

#include "VanimCore/Entity.h"

#include <vector>

namespace Vanim
{
	class State
	{
	public:
		State() = default;
		~State() = default;
		
		virtual void Create() {}

		virtual void Update(const double deltaTime);

		virtual void Draw() {}

		// virtual void Event() {}

		virtual void Destroy();

		Entity CreateEntity(const char* tag = "Entity");

		void DestroyEntity(const Entity& entity);

		template<typename Component>
		std::vector<Entity> GetEntitiesOfType()
		{
			auto view = _registry.view<Component>();
			std::vector<Entity> entities;
			entities.reserve(view.size());
			for (auto entity : view)
			{
				entities.emplace_back(entity, &_registry);
			}
			return entities;
		}

		
		template<typename... Components>
		std::vector<Entity> GetEntitiesOfTypes()
		{
			auto group = _registry.group<Components...>();
			std::vector<Entity> entities;
			entities.reserve(group.size());
			for (auto entity : group)
			{
				entities.emplace_back(entity, &_registry);
			}
			return entities;
		}
	protected:
		entt::registry _registry;
	};
}
