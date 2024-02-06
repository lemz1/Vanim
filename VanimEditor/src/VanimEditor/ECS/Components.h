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
		Camera camera;
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

	struct NativeScriptComponent
	{
	public:
		NativeScriptComponent() = default;
		NativeScriptComponent(const NativeScriptComponent&) = default;

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->instance; nsc->instance = nullptr; };
		}
	public:
		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		ScriptableEntity* instance;
	};
}

