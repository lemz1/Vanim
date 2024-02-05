#pragma once

#include <glm/glm.hpp>

#include "ScriptableEntity.h"
#include "VanimEditor/Rendering/Camera.h"

namespace Vanim
{
	struct TransformComponent
	{
	public:
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: transform(transform)
		{}
	public:
		glm::mat4 transform{ 1.0f };
	};

	struct CameraComponent
	{
	public:
		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(const Camera& camera) 
		:	camera(camera)
		{}
	public:
		Camera		camera;
	};

	struct NativeScriptComponent
	{
	public:
		NativeScriptComponent() = default;
		NativeScriptComponent(const NativeScriptComponent&) = default;

		template<typename T>
		void Bind()
		{
			InstantiateFunction = [&]() { _instance = new T(); };
			DestroyInstanceFunction = [&]() { delete (T*)_instance; _instance = nullptr; };

			CreateFunction = [](ScriptableEntity* instance) { ((T*)instance)->Create(); };
			UpdateFunction = [](ScriptableEntity* instance, const double deltaTime) { ((T*)instance)->Update(deltaTime); };
			DestroyFunction = [](ScriptableEntity* instance) { ((T*)instance)->Destroy(); };
		}
	public:
		std::function<void()> InstantiateFunction;
		std::function<void()> DestroyInstanceFunction;

		std::function<void(ScriptableEntity*)> CreateFunction;
		std::function<void(ScriptableEntity*, const double)> UpdateFunction;
		std::function<void(ScriptableEntity*)> DestroyFunction;
	private:
		ScriptableEntity* _instance;
		friend class State;
	};

	struct TagComponent
	{
	public:
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const char* tag)
		:	tag(tag)
		{}
	public:
		const char* tag;
	};
}

