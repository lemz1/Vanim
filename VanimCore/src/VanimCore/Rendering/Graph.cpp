#include "corepch.h"
#include "Graph.h"

#include "VanimCore/Math/Math.h"

namespace Vanim
{
	Graph::Graph(const GraphSpecification& spec)
	:	lineWidth(spec.lineWidth),
		color(spec.color)
	{}

	void Graph::CalculateCoordinates(
		float (*Function)(float),
		const GraphData& data
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

		// x = left, y = right, z = bottom, w = top
		glm::vec4 bounds = glm::vec4(FLT_MAX, -FLT_MAX, FLT_MAX, -FLT_MAX);

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

				float actualLineWidth = lineWidth * 0.01f;
				glm::vec2 vertexOffset = rotatedDir * (actualLineWidth / 2.0f);

				// padding is currently not perfect
				// but still enough to minimize blank space
				// between quads
				glm::vec2 extraPadding = dir * (actualLineWidth / 2.0f);
				if (i == segment.size() - 2) // dont add padding to last quad
				{
					extraPadding = glm::vec2(0);
				}

				glm::vec2 p1_1 = p1 + vertexOffset;
				glm::vec2 p1_2 = p1 - vertexOffset;
				
				glm::vec2 p2_1 = p2 + vertexOffset + extraPadding;
				glm::vec2 p2_2 = p2 - vertexOffset + extraPadding;

				{ // update bounds if necessary (bounds needed for texCoord calculation)
					bounds.x = Math::Min(bounds.x, p1_1.x);
					bounds.y = Math::Max(bounds.y, p1_1.x);
					bounds.z = Math::Min(bounds.z, p1_1.y);
					bounds.w = Math::Max(bounds.w, p1_1.y);

					bounds.x = Math::Min(bounds.x, p1_2.x);
					bounds.y = Math::Max(bounds.y, p1_2.x);
					bounds.z = Math::Min(bounds.z, p1_2.y);
					bounds.w = Math::Max(bounds.w, p1_2.y);

					bounds.x = Math::Min(bounds.x, p2_1.x);
					bounds.y = Math::Max(bounds.y, p2_1.x);
					bounds.z = Math::Min(bounds.z, p2_1.y);
					bounds.w = Math::Max(bounds.w, p2_1.y);

					bounds.x = Math::Min(bounds.x, p2_2.x);
					bounds.y = Math::Max(bounds.y, p2_2.x);
					bounds.z = Math::Min(bounds.z, p2_2.y);
					bounds.w = Math::Max(bounds.w, p2_2.y);
				}

				vertices.emplace_back(p1_1);
				vertices.emplace_back(p1_2);

				vertices.emplace_back(p2_1);
				vertices.emplace_back(p2_2);
				

				indices.emplace_back(vertexIndex + 0);
				indices.emplace_back(vertexIndex + 1);
				indices.emplace_back(vertexIndex + 2);
				
				indices.emplace_back(vertexIndex + 1);
				indices.emplace_back(vertexIndex + 3);
				indices.emplace_back(vertexIndex + 2);

				vertexIndex += 4;
			}
		}

		std::vector<glm::vec2> texCoords;
		texCoords.reserve(vertices.size());
		for (auto& vertex : vertices)
		{
			texCoords.emplace_back(
				Math::InverseLerp(bounds.x, bounds.y, vertex.x),
				Math::InverseLerp(bounds.z, bounds.w, vertex.y)
			);
		}

		_vao = MakeShared<VertexArray>();

		_vbo = MakeShared<VertexBuffer>(sizeof(glm::vec2) * vertices.size(), vertices.data());
		_tcbo = MakeShared<VertexBuffer>(sizeof(glm::vec2) * texCoords.size(), texCoords.data());
		_ibo = MakeShared<IndexBuffer>(sizeof(GLuint) * indices.size(), indices.data());

		_vao->LinkVertexBuffer(*_vbo, 0, GL_FLOAT, GL_FALSE, 2, 0, sizeof(glm::vec2));
		_vao->LinkVertexBuffer(*_tcbo, 1, GL_FLOAT, GL_FALSE, 2, 0, sizeof(glm::vec2));
		_vao->LinkIndexBuffer(*_ibo);
	}
}