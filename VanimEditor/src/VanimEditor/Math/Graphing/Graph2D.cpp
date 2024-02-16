#include "editorpch.h"
#include "Graph2D.h"

namespace Vanim
{
	Graph2D::Graph2D(const GraphSpecification2D& spec)
	:	lineWidth(spec.lineWidth),
		color(spec.color)
	{
		ShaderInfo infos[] = {
		ShaderInfo
		{
			"assets/shaders/Graph2D.vert.glsl",
			ShaderType::VertexShader
		},
		ShaderInfo
		{
			"assets/shaders/Graph2D.frag.glsl",
			ShaderType::FragmentShader
		}
		};

		_shader = MakeUnique<Shader>(2, infos);

		_colorID = _shader->GetUniformLocation("u_Color");
	}

	void Graph2D::CalculateCoordinates(
		float (*Function)(float),
		const GraphData2D& data
	)
	{
		size_t segments = data.excludes.size() + 1;

		std::vector<std::vector<glm::vec2>> coordinates;
		coordinates.resize(segments);

		size_t segmentIndex = 0;

		float increment = Math::Abs(data.increment); // no negative values
		if (increment == 0)
		{
			increment = 0.01f;
		}

		float lastX = data.minX;
		float x = data.minX;

		size_t numCoordinates = 0;
		while (true)
		{
			if (data.excludes.size() > segmentIndex && x >= data.excludes.at(segmentIndex))
			{
				coordinates.at(segmentIndex).pop_back(); // pop duplicate coordinate
				numCoordinates--;

				lastX = x;
				x = data.excludes.at(segmentIndex) + increment;
				segmentIndex++;
				continue;
			}

			if (lastX < data.maxX && x > data.maxX)
			{
				x = data.maxX; // make sure that maxX is included
			}

			if (x > data.maxX)
			{
				coordinates.at(segmentIndex).pop_back(); // pop duplicate coordinate
				numCoordinates--;
				break;
			}

			float y = Function(x);

			if (coordinates.at(segmentIndex).size() > 0) // not the first coordinate
			{
				coordinates.at(segmentIndex).emplace_back(x, y);
				numCoordinates++;
			}

			coordinates.at(segmentIndex).emplace_back(x, y);
			numCoordinates++;


			lastX = x;
			x += increment;
		}

		std::vector<glm::vec2> vertices;
		vertices.reserve(numCoordinates * 2);

		std::vector<GLuint> indices;
		_numIndices = numCoordinates * 3;
		indices.reserve(_numIndices);

		size_t vertexIndex = 0;
		for (auto& segment : coordinates)
		{
			for (size_t i = 0; i < segment.size() - 1; i += 2)
			{
				glm::vec2 p1 = segment.at(i);
				glm::vec2 p2 = segment.at(i + 1);

				glm::vec2 dir = glm::normalize(p2 - p1);

				// rotate direction around 90 degrees
				constexpr float angle = glm::radians(90.0f);

				glm::mat2 rotationMatrix(
					cos(angle), -sin(angle),
					sin(angle),  cos(angle)
				);

				glm::vec2 rotatedDir = rotationMatrix * dir;

				float actualLineWidth = lineWidth * 0.0025f;
				glm::vec2 vertexOffset = rotatedDir * (actualLineWidth / 2.0f);

				// padding is currently not perfect
				// but still enough to minimize blank space
				// between quads
				glm::vec2 extraPadding = dir * (actualLineWidth / 2.0f);
				if (i == segment.size() - 2) // dont add padding to last quad
				{
					extraPadding = glm::vec2(0);
				}
				
				vertices.emplace_back(p1 + vertexOffset);
				vertices.emplace_back(p1 - vertexOffset);

				vertices.emplace_back(p2 + vertexOffset + extraPadding);
				vertices.emplace_back(p2 - vertexOffset + extraPadding);
				

				indices.emplace_back(vertexIndex + 0);
				indices.emplace_back(vertexIndex + 1);
				indices.emplace_back(vertexIndex + 2);
				
				indices.emplace_back(vertexIndex + 1);
				indices.emplace_back(vertexIndex + 3);
				indices.emplace_back(vertexIndex + 2);

				vertexIndex += 4;
			}
		}

		_vao = MakeUnique<VertexArray>();

		_vbo = MakeUnique<VertexBuffer>(sizeof(glm::vec2) * vertices.size(), vertices.data());
		_ibo = MakeUnique<IndexBuffer>(sizeof(GLuint) * indices.size(), indices.data());

		_vao->LinkVertexBuffer(*_vbo, 0, GL_FLOAT, GL_FALSE, 2, 0, sizeof(glm::vec2));
		_vao->LinkIndexBuffer(*_ibo);
	}

	void Graph2D::Draw()
	{
		_shader->Bind();
		_shader->SetFloats(_colorID, color.r, color.g, color.b, color.a);

		_vao->Bind();

		glLineWidth(lineWidth);
		
		glDrawElements(GL_TRIANGLES, _numIndices, GL_UNSIGNED_INT, nullptr);

		_vao->Unbind();

		_shader->Unbind();
	}
}
