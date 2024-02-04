#pragma once

#include <entt/entt.hpp>
#include <stdint.h>

namespace Vanim
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(
			entt::entity handle, 
			entt::registry* registry
		) 
		:	_handle(handle), 
			_registry(registry)
		{}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return _registry->emplace<T>(_handle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			return _registry->get<T>(_handle);
		}

		template<typename T>
		void RemoveComponent()
		{
			_registry->remove<T>(_handle);
		}

		template<typename... T>
		bool HasAnyOf()
		{
			return _registry->any_of<T...>(_handle);
		}

		template<typename... T>
		bool HasAllOf()
		{
			return _registry->any_of<T...>(_handle);
		}

		const entt::entity GetEntity() const { return _handle; }
	private:
		entt::registry* _registry;
		entt::entity _handle;
	};
}
