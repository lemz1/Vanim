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

		template<typename... T>
		std::tuple<std::reference_wrapper<T>...> GetComponents()
		{
			return _registry->get<T...>(_handle);
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
			return _registry->all_of<T...>(_handle);
		}

		const entt::entity GetEntity() const { return _handle; }

		bool operator==(const Entity& other) const { return _handle == other._handle && _registry == other._registry; }
		bool operator!=(const Entity& other) const { return !operator==(other); }
		operator bool() const { return _handle != entt::null; }
		operator uint32_t() const { return (uint32_t)_handle; }
	private:
		entt::registry* _registry = nullptr;
		entt::entity _handle{ entt::null };
	};
}
