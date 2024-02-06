#pragma once

#include <vector>

#include "Entity.h"
#include "Components.h"

namespace Vanim
{
	class Scene
	{
	public:
		Scene() = default;

		Entity CreateEntity(const char* tag = "Entity");

		void DestroyEntity(const Entity& entity);

		void Update(const double deltaTime);
		void Destroy();

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
	private:
		entt::registry _registry;

		friend class SceneHierarchyPanel;
	};
}
