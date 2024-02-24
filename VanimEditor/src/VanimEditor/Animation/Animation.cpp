#include "editorpch.h"
#include "Animation.h"

namespace Vanim
{
	Animation::Animation(
		const char* fragmentPath, 
		std::vector<Entity>& entities
	)
	:	_shader(nullptr)
	{
		ShaderInfo infos[] =
		{
			ShaderInfo
			{
				"Assets/Shaders/Default.vert",
				ShaderType::VertexShader
			},
			ShaderInfo
			{
				fragmentPath,
				ShaderType::FragmentShader
			}
		};

		_shader = MakeShared<Shader>(2, infos);

		_shader->Bind();

		_viewProjectionID = _shader->GetUniformLocation("u_ViewProjection");
		_modelMatrixID = _shader->GetUniformLocation("u_ModelMatrix");
		_progressID = _shader->GetUniformLocation("u_Progress");
		_colorID = _shader->GetUniformLocation("u_Color");

		_shader->Unbind();

		for (auto& entity : entities)
		{
			auto& ac = entity.GetComponent<RenderingComponent>();

			ac.shader = _shader;
			ac.viewProjectionID = _viewProjectionID;
			ac.modelMatrixID = _modelMatrixID;
			ac.colorID = _colorID;
		}
	}

	void Animation::Play(float progress)
	{
		_shader->Bind();
		_shader->SetFloat(_progressID, progress);
		_shader->Unbind();
	}
}
