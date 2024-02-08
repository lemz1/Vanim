#include "editorpch.h"
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

	void Renderer::DrawQuad(
		const glm::mat4& transform, 
		const glm::mat4& view, 
		const glm::mat4& projection,
		const glm::vec4& color
	)
	{
		glm::mat4 modelViewProjection = view * projection * transform;

		_instance->_shaderQuad->Bind();
		_instance->_vertexArrayQuad->Bind();

		GLuint uColor = _instance->_shaderQuad->GetUniformLocation("u_Color");
		_instance->_shaderQuad->SetFloats(uColor, color.r, color.g, color.b, color.a);

		GLuint uModelViewProjection = _instance->_shaderQuad->GetUniformLocation("u_ModelViewProjection");
		_instance->_shaderQuad->Set4x4Matrix(uModelViewProjection, 1, false, (GLfloat*)&modelViewProjection);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		_instance->_vertexArrayQuad->Unbind();
		_instance->_shaderQuad->Unbind();
	}
}
