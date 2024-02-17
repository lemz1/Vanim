#include "corepch.h"
#include "Renderer.h"

namespace Vanim
{
	Renderer* Renderer::_instance = nullptr;

	Renderer::Renderer()
	{
		if (_instance)
		{
			return;
		}

		_instance = this;

		_vertexArrayQuad = MakeUnique<VertexArray>();
		
		ShaderInfo infos[] = {
			ShaderInfo
			{
				"assets/shaders/quad.vert.glsl",
				ShaderType::VertexShader
			},
			ShaderInfo
			{
				"assets/shaders/quad.frag.glsl",
				ShaderType::FragmentShader
			}
		};

		_shaderQuad = MakeUnique<Shader>(2, infos);
	}

	Renderer::~Renderer()
	{
		_instance = nullptr;
	}

	void Renderer::SetViewProjection(
		const glm::mat4& view, 
		const glm::mat4& projection
	)
	{
		_instance->_shaderQuad->Bind();

		glm::mat4 viewProjection = projection * glm::inverse(view);

		GLuint uViewProjection = _instance->_shaderQuad->GetUniformLocation("u_ViewProjection");
		_instance->_shaderQuad->Set4x4Matrix(uViewProjection, 1, false, (GLfloat*)&viewProjection);
		
		_instance->_shaderQuad->Unbind();
	}

	void Renderer::DrawQuad(
		const glm::mat4& transform, 
		const glm::vec4& color
	)
	{
		_instance->_shaderQuad->Bind();
		_instance->_vertexArrayQuad->Bind();

		GLuint uColor = _instance->_shaderQuad->GetUniformLocation("u_Color");
		_instance->_shaderQuad->SetFloats(uColor, color.r, color.g, color.b, color.a);

		GLuint uModel = _instance->_shaderQuad->GetUniformLocation("u_Model");
		_instance->_shaderQuad->Set4x4Matrix(uModel, 1, false, (GLfloat*)&transform);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		_instance->_vertexArrayQuad->Unbind();
		_instance->_shaderQuad->Unbind();
	}

	void Renderer::DrawMesh2D(
		const Mesh2D& mesh, 
		const glm::mat4& transform, 
		const glm::vec4& color
	)
	{
		mesh._shader->Bind();

		mesh._vao->Bind();

		glDrawElements(GL_TRIANGLES, mesh._indices.size(), GL_UNSIGNED_INT, nullptr);

		mesh._vao->Unbind();

		mesh._shader->Unbind();
	}

	void Renderer::DrawGraph2D(
		const Graph2D& graph, 
		const glm::mat4& transform,
		const glm::mat4& viewProjection
	)
	{
		graph._shader->Bind();

		graph._shader->Set4x4Matrix(graph._viewProjID, 1, false, (GLfloat*)&viewProjection);
		graph._shader->Set4x4Matrix(graph._modelID, 1, false, (GLfloat*)&transform);
		
		graph._shader->SetFloats(graph._colorID, graph.color.r, graph.color.g, graph.color.b, graph.color.a);

		graph._vao->Bind();

		glLineWidth(graph.lineWidth);

		glDrawElements(GL_TRIANGLES, graph._numIndices, GL_UNSIGNED_INT, nullptr);

		graph._vao->Unbind();

		graph._shader->Unbind();
	}
}
