#pragma once

#include "VanimCore/Base.h"

#include "VanimCore/OpenGL/VertexArray.h"
#include "VanimCore/OpenGL/Shader.h"

#include <glm/glm.hpp>

namespace Vanim
{
	class Renderer
	{
	public:
		static void DrawMesh(
			const Shared<Shader>& shader,
			const Shared<VertexArray>& vao,
			GLsizei numIndices
		);
	};
}
