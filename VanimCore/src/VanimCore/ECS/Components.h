#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "VanimCore/Base.h"

#include "ScriptableEntity.h"
#include "VanimCore/Rendering/Graph2D.h"
#include "VanimCore/Rendering/Camera.h"
#include "VanimCore/Rendering/Mesh2D.h"

#include <vector>

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
		void Bind() const
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->instance; nsc->instance = nullptr; };
		}
	public:
		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		ScriptableEntity* instance;
	};

	struct Layer2DComponent
	{
	public:
		Layer2DComponent() = default;
		Layer2DComponent(const Layer2DComponent&) = default;
		Layer2DComponent(uint32_t layer)
		:	layer(layer)
		{}
	public:
		uint32_t layer;
	};

	struct Mesh2DComponent
	{
	public:
		Mesh2DComponent() = default;
		Mesh2DComponent(const Mesh2DComponent&) = delete;
		Mesh2DComponent(
			std::vector<glm::vec2> vertices,
			std::vector<glm::vec2> texCoords,
			std::vector<GLuint> indices,
			const Shared<Shader>& shader
		)
		:	mesh(vertices, texCoords, indices, shader)
		{}
	public:
		Mesh2D mesh;
	};

	struct Graph2DComponent
	{
	public:
		Graph2DComponent() = default;
		Graph2DComponent(const Graph2DComponent&) = delete;
		Graph2DComponent(const GraphSpecification2D& spec = {})
		:	graph(spec)
		{}
	public:
		Graph2D graph;
	};
}

