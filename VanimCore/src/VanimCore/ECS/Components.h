#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "VanimCore/Base.h"

#include "ScriptableEntity.h"

#include "VanimCore/Rendering/AnimationShader.h"
#include "VanimCore/Rendering/Camera.h"
#include "VanimCore/Rendering/Graph.h"
#include "VanimCore/Rendering/Mesh.h"

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

	struct AnimationComponent
	{
	public:
		AnimationComponent() = delete;
		AnimationComponent(const AnimationComponent&) = default;
		AnimationComponent(
			const Shared<Shader>& shader,
			const Shared<VertexArray>& vao,
			GLsizei numIndices
		)
		:	shader(MakeShared<AnimationShader>(shader)),
			_vao(vao),
			_numIndices(numIndices)
		{}

		AnimationComponent(
			const Shared<AnimationShader>& shader,
			const Shared<VertexArray>& vao,
			GLsizei numIndices
		)
		:	shader(shader),
			_vao(vao),
			_numIndices(numIndices)
		{}

		const Shared<VertexArray>& GetVAO() const { return _vao; }
		GLsizei NumIndices() const { return _numIndices; }
	public:
		Shared<AnimationShader> shader;

		glm::vec4 color = Color::fireBrick;
	private:
		Shared<VertexArray> _vao;
		GLsizei _numIndices;
	};

	struct LayerComponent
	{
	public:
		LayerComponent() = default;
		LayerComponent(const LayerComponent&) = default;
		LayerComponent(uint32_t layer)
		:	layer(layer)
		{}
	public:
		uint32_t layer;
	};

	struct MeshComponent
	{
	public:
		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = delete;
		MeshComponent(
			std::vector<glm::vec2> vertices,
			std::vector<glm::vec2> texCoords,
			std::vector<GLuint> indices
		)
		:	mesh(vertices, texCoords, indices)
		{}
	public:
		Mesh mesh;
	};

	struct GraphComponent
	{
	public:
		GraphComponent() = default;
		GraphComponent(const GraphComponent&) = delete;
		GraphComponent(const GraphSpecification& spec = {})
		:	graph(spec)
		{}
	public:
		Graph graph;
	};
}

