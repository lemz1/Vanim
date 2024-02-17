#pragma once

#include "VanimCore/Base.h"
#include "VanimCore/Util/Color.h"
#include "VanimCore/OpenGL/VertexArray.h"
#include "VanimCore/OpenGL/Shader.h"

#include <glm/glm.hpp>
#include <vector>

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
	public:
		float		lineWidth;
		glm::vec4	color;
	private:
		size_t _numIndices = 0;

		Unique<Shader> _shader; // should probably be in renderer.cpp

		Unique<VertexArray> _vao;
		Unique<VertexBuffer> _vbo;
		Unique<IndexBuffer> _ibo;

		GLuint _colorID = 0;
		GLuint _viewProjID = 0;
		GLuint _modelID = 0;

		friend class Renderer;
	};
}
