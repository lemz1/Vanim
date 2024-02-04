#pragma once

#include "Entity.h"

namespace Vanim
{
	class ScriptableEntity
	{
	public:
		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return _entity.AddComponent<T>(Args...);
		}

		template<typename T>
		T& GetComponent()
		{
			return _entity.GetComponent<T>();
		}

		template<typename T>
		void RemoveComponent()
		{
			_entity.RemoveComponent<T>();
		}

		template<typename... T>
		bool HasAnyOf()
		{
			return _entity.HasAnyOf<T...>();
		}

		template<typename... T>
		bool HasAllOf()
		{
			return _entity.HasAllOf<T...>();
		}
	private:
		Entity _entity;
		friend class State;
	};
}
