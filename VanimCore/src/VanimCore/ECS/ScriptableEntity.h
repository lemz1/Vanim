#pragma once

#include "Entity.h"

namespace Vanim
{
	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity() {}

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

		template<typename... T>
		std::tuple<std::reference_wrapper<T>...> GetComponents()
		{
			return _entity.GetComponents<T...>();
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
	protected:
		virtual void Create() {};
		virtual void Update(const double deltaTime) {};
		virtual void Destroy() {};
	private:
		Entity _entity;
		friend class Scene;
	};
}
