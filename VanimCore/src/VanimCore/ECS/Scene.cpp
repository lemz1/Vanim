#include "corepch.h"
#include "Scene.h"

namespace Vanim
{
    Entity Scene::CreateEntity(const char* tag)
    {
        Entity entity = Entity(_registry.create(), &_registry);
        entity.AddComponent<TagComponent>(tag);
        return entity;
    }

    void Scene::DestroyEntity(const Entity& entity)
    {
        _registry.destroy(entity.GetEntity());
    }

    void Scene::Update(const double deltaTime)
    {
        for (auto& entity : GetEntitiesOfType<NativeScriptComponent>())
        {
            auto& nsc = entity.GetComponent<NativeScriptComponent>();

            if (!nsc.instance)
            {
                nsc.instance = nsc.InstantiateScript();
                nsc.instance->Create();
                nsc.instance->_entity = entity;
            }

            nsc.instance->Update(deltaTime);
        }
    }

    void Scene::Destroy()
    {
        for (auto& entity : GetEntitiesOfType<NativeScriptComponent>())
        {
            auto& nsc = entity.GetComponent<NativeScriptComponent>();

            if (nsc.instance)
            {
                nsc.instance->Destroy();
                nsc.DestroyScript(&nsc);
            }
        }
    }
}
