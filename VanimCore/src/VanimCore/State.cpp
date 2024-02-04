#include "vanimpch.h"
#include "State.h"

#include "VanimCore/Components.h"

namespace Vanim
{
	void State::Update(const double deltaTime)
	{
		auto entities = GetEntitiesOfType<NativeScriptComponent>();
		for (auto& entity : entities)
		{
			auto& script = entity.GetComponent<NativeScriptComponent>();
			if (!script._instance)
			{
				script.InstantiateFunction();
				script._instance->_entity = entity;
				if (script.CreateFunction)
				{
					script.CreateFunction(script._instance);
				}
			}

			if (script.UpdateFunction)
			{
				script.UpdateFunction(script._instance, deltaTime);
			}
		}
	}

	void State::Destroy()
	{
		auto entities = GetEntitiesOfType<NativeScriptComponent>();
		for (auto& entity : entities)
		{
			auto script = entity.GetComponent<NativeScriptComponent>();
			if (script._instance)
			{
				if (script.DestroyFunction)
				{
					script.DestroyFunction(script._instance);
				}
				script.DestroyInstanceFunction();
			}
		}
	}

	Entity State::CreateEntity(
		const char* tag
	)
	{
		Entity entity = Entity(_registry.create(), &_registry);
		entity.AddComponent<TagComponent>(tag);
		return entity;
	}

	void State::DestroyEntity(const Entity& entity)
	{
		_registry.destroy(entity.GetEntity());
	}
}
