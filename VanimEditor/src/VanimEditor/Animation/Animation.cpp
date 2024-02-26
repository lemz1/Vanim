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
		_shader = MakeShared<RenderShader>("Assets/Shaders/Default.vert", fragmentPath);

		_shader->GetShader()->Bind();

		_progressID = _shader->GetShader()->GetUniformLocation("u_Progress");

		_shader->GetShader()->Unbind();

		for (auto& entity : entities)
		{
			auto& ac = entity.GetComponent<RenderingComponent>();

			ac.shader = _shader;
		}
	}

	void Animation::Play(float progress)
	{
		_shader->GetShader()->Bind();
		_shader->GetShader()->SetFloat(_progressID, progress);
		_shader->GetShader()->Unbind();
	}
}
