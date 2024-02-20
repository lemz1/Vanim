#include "corepch.h"
#include "AnimationShader.h"

namespace Vanim
{
	AnimationShader::AnimationShader(const Shared<Shader>& shader)
	:	_shader(shader),
		_viewProjectionID(-1),
		_modelMatrixID(-1),
		_colorID(-1)
	{
		_shader->Bind();

		_viewProjectionID = _shader->GetUniformLocation("u_ViewProjection");
		_modelMatrixID = _shader->GetUniformLocation("u_ModelMatrix");
		_colorID = _shader->GetUniformLocation("u_Color");

		_shader->Unbind();
	}

	void AnimationShader::SetViewProjection(const glm::mat4 viewProjection)
	{
		_shader->Bind();
		_shader->Set4x4Matrix(_viewProjectionID, 1, false, (GLfloat*)&viewProjection);
		_shader->Unbind();
	}

	void AnimationShader::SetViewProjection(
		const glm::mat4& view, 
		const glm::mat4& projection
	)
	{
		glm::mat4 viewProjection = projection * glm::inverse(view);
		_shader->Bind();
		_shader->Set4x4Matrix(_viewProjectionID, 1, false, (GLfloat*)&viewProjection);
		_shader->Unbind();
	}

	void AnimationShader::SetModelMatrix(const glm::mat4& modelMatrix)
	{
		_shader->Bind();
		_shader->Set4x4Matrix(_modelMatrixID, 1, false, (GLfloat*)&modelMatrix);
		_shader->Unbind();
	}

	void AnimationShader::SetColor(const glm::vec4& color)
	{
		_shader->Bind();
		_shader->SetFloats(_colorID, color.r, color.g, color.b, color.a);
		_shader->Unbind();
	}
}
