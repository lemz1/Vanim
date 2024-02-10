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
}
