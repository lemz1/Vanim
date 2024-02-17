#pragma once

#include "VanimCore/Base.h"

#include "VanimCore/OpenGL/VertexArray.h"
#include "VanimCore/OpenGL/Shader.h"
#include "VanimCore/Rendering/Graph2D.h"
#include "VanimCore/Rendering/Mesh2D.h"

#include <glm/glm.hpp>

namespace Vanim
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		static void SetViewProjection(
			const glm::mat4& view,
			const glm::mat4& projection
		);

		static void DrawQuad(
			const glm::mat4& transform,
			const glm::vec4& color
		);

		static void DrawMesh2D(
			const Mesh2D& mesh,
			const glm::mat4& transform,
			const glm::vec4& color
		);

		static void DrawGraph2D(
			const Graph2D& graph,
			const glm::mat4& transform,
			const glm::mat4& viewProjection
		);
	private:
		static Renderer* _instance;

		Unique<VertexArray> _vertexArrayQuad;
		Unique<Shader> _shaderQuad;
	};
}
