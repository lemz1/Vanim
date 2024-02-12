#include "editorpch.h"
#include "Graph.h"

namespace Vanim
{
	void Graph::CalculateCoordinates(
		float (*Function)(float),
		const GraphData2D& data
	)
	{
		ShaderInfo infos[] = {
			ShaderInfo
			{
				"assets/shaders/default.vert.glsl",
				ShaderType::VertexShader
			},
			ShaderInfo
			{
				"assets/shaders/default.frag.glsl",
				ShaderType::FragmentShader
			}
		};

		_shader = MakeUnique<Shader>(2, infos);

		size_t segments = data.excludes.size() + 1;
		size_t segmentIndex = 0;
		size_t segmentVertexIndex = 0;

		float increment = Math::Abs(data.increment); // no negative values
		if (increment == 0)
		{
			increment = 0.01f;
		}

		float lastX = data.minX;
		float x = data.minX;
		while (true)
		{
			if (data.excludes.size() > segmentIndex && x >= data.excludes.at(segmentIndex))
			{
				_vertices.pop_back(); // pop the duplicate
				lastX = x;
				x += increment;
				segmentIndex++;
				segmentVertexIndex = 0;
				continue;
			}

			if (lastX < data.maxX && x > data.maxX)
			{
				x = data.maxX; // make sure that maxX is included
			}

			if (x > data.maxX)
			{
				_vertices.pop_back(); // pop the duplicate
				break;
			}

			float y = Function(x);

			_vertices.emplace_back(x, y, 0.f);
			
			if (segmentVertexIndex > 0)
			{
				_vertices.emplace_back(x, y, 0.f);
			}

			lastX = x;
			x += increment;
			segmentVertexIndex++;
		}

		if (_vertices.size() < 2)
		{
			VANIM_ERROR("Function returns less than 2 points");
			return;
		}
		else if (_vertices.size() % 2 != 0)
		{
			VANIM_ERROR("Function should return an even amount of points");
			return;
		}

		_vao = MakeUnique<VertexArray>();

		_vbo = MakeUnique<VertexBuffer>(sizeof(glm::vec3) * _vertices.size(), _vertices.data());

		_vao->LinkVertexBuffer(*_vbo, 0, GL_FLOAT, GL_FALSE, 3, 0, sizeof(glm::vec3));
	}

	void Graph::CalculateCoordinates(
		float (*Function)(const glm::vec2&),
		const GraphData3D& data
	)
	{
	
	}

	void Graph::Draw()
	{
		_shader->Bind();

		_vao->Bind();

		glLineWidth(2.f);

		glDrawArrays(GL_LINES, 0, _vertices.size());

		_vao->Unbind();

		_shader->Unbind();
	}
}
