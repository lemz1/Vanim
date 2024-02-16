#pragma once

#include "VanimCore.h"

#include <glm/glm.hpp>
#include <vector>

#include "VanimEditor/Util/Color.h"

namespace Vanim
{
	struct GraphSpecification2D
	{
		float		lineWidth = 5.f;
		glm::vec4	color = Color::salmon;
	};

	struct GraphData2D
	{
		float minX = -5.0f, maxX = 5.0f, increment = 0.01f;
		std::vector<float> excludes = {};
	};

	class Graph2D
	{
	public:
		Graph2D(const GraphSpecification2D& spec = {});

		void CalculateCoordinates(
			float (*Function)(float), 
			const GraphData2D& data
		);

		void Draw();
	public:
		float		lineWidth;
		glm::vec4	color;
	private:
		size_t _numIndices = 0;

		Unique<Shader> _shader;

		Unique<VertexBuffer> _vbo;
		Unique<VertexArray> _vao;
		Unique<IndexBuffer> _ibo;

		GLuint _colorID = 0;
	};
}
