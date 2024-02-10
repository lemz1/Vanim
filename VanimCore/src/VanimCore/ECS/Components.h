#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "VanimCore/Base.h"

#include "ScriptableEntity.h"
#include "VanimCore/Rendering/Camera.h"

namespace Vanim
{
	struct TransformComponent
	{
	public:
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(
			const glm::vec3 position
		)
		:	position(position)
		{}

		glm::mat4 AsMat4() const
		{
			return glm::translate(glm::mat4(1.f), position) 
				 * glm::mat4_cast(rotation) 
				 * glm::scale(glm::mat4(1.f), scale);
		}
	public:
		glm::vec3 position{ 0.f, 0.f, 0.f };
		glm::quat rotation{ 1.0f, 0.f, 0.f, 0.f };
		glm::vec3 scale{ 1.f, 1.f, 1.f };
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

