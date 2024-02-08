#pragma once

#include "VanimCore.h"

#include "VanimCore/OpenGL/VertexArray.h"

#include <glm/glm.hpp>

namespace Vanim
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		static void DrawQuad(
			const glm::mat4& transform,
			const glm::mat4& view,
			const glm::mat4& projection,
			const glm::vec4& color
		);
	private:
		static Renderer* _instance;

		Unique<VertexArray> _vertexArrayQuad;
		Unique<Shader> _shaderQuad;
	};
}
