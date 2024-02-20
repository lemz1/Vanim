#pragma once

#include "VanimCore/Base.h"
#include "VanimCore/Util/Color.h"
#include "VanimCore/OpenGL/VertexArray.h"
#include "VanimCore/OpenGL/Shader.h"

#include <glm/glm.hpp>
#include <vector>

namespace Vanim
{
	struct GraphSpecification
	{
		float		lineWidth = 5.f;
		glm::vec4	color = Color::salmon;
	};

	struct GraphData
	{
		float				minX = -5.0f;
		float				maxX = 5.0f; 
		float				increment = 0.01f;
		std::vector<float>	excludes = {};
	};

	class Graph
	{
	public:
		Graph(const GraphSpecification& spec = {});

		void CalculateCoordinates(
			float (*Function)(float), 
			const GraphData& data
		);

		const Shared<VertexArray>& GetVAO() const { return _vao; }
		const GLsizei NumIndices() const { return _numIndices; }
	public:
		float		lineWidth;
		glm::vec4	color;
	private:
		GLsizei _numIndices = 0;

		Shared<VertexArray> _vao;
		Shared<VertexBuffer> _vbo;
		Shared<VertexBuffer> _tcbo;
		Shared<IndexBuffer> _ibo;

		friend class Renderer;
	};
}
