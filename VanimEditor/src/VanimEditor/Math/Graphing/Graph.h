#pragma once

/*
* we need to have a function f(x) which returns a y value
* we then create multiple quads that visualize the graph
* we then do batch rendering meaning doing one draw call
* but rendering multiple quads
*/
#include "VanimCore.h"

#include <glm/glm.hpp>
#include <vector>

namespace Vanim
{
	struct GraphData2D
	{
		float minX = -5.0f, maxX = 5.0f, increment = 0.01f;
		std::vector<float> excludes = {};
	};

	struct GraphData3D
	{
		glm::vec2 minXY = { -5.0f, -5.0f }, maxX = { 5.0f, 5.0f }, increment = { 0.01f, 0.01f };
		std::vector<glm::vec2> excludes = {};
	};

	class Graph
	{
	public:
		void CalculateCoordinates(
			float (*Function)(float), 
			const GraphData2D& data
		);
		void CalculateCoordinates(
			float (*Function)(const glm::vec2&), 
			const GraphData3D& data
		);

		void Draw();
	private:
		std::vector<glm::vec3> _vertices;

		Unique<Shader> _shader;

		Unique<VertexBuffer> _vbo;
		Unique<VertexArray> _vao;
	};
}
