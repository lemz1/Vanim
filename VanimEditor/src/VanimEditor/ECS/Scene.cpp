#include "editorpch.h"
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
}
