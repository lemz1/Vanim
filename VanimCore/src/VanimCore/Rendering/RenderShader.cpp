#include "corepch.h"
#include "RenderShader.h"

namespace Vanim
{
	RenderShader::RenderShader(
		const char* vertexPath, 
		const char* fragmentPath
	)
	{
		ShaderInfo infos[] =
		{
			ShaderInfo 
			{
				vertexPath,
				ShaderType::VertexShader
			},
			ShaderInfo
			{
				fragmentPath,
				ShaderType::FragmentShader
			},
		};

		_shader = MakeShared<Shader>(2, infos);

		_shader->Bind();

		_viewProjectionID = _shader->GetUniformLocation("u_ViewProjection");
		_modelMatrix = _shader->GetUniformLocation("u_ModelMatrix");
		_colorID = _shader->GetUniformLocation("u_Color");

		_shader->Unbind();
	}
	RenderShader::RenderShader(const Shared<Shader>& shader)
	:	_shader(shader)
	{
		_shader->Bind();

		_viewProjectionID = _shader->GetUniformLocation("u_ViewProjection");
		_modelMatrix = _shader->GetUniformLocation("u_ModelMatrix");
		_colorID = _shader->GetUniformLocation("u_Color");

		_shader->Unbind();
	}
}
