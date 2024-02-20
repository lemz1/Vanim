#include "editorpch.h"
#include "CreateAnimation.h"

namespace Vanim
{
	CreateAnimation::CreateAnimation(std::vector<Entity>& entities)
	:	_entities(entities)
	{
		ShaderInfo infos[] = {
			ShaderInfo
			{
				"Assets/Shaders/default.vert.glsl",
				ShaderType::VertexShader
			},
			ShaderInfo
			{
				"Assets/Shaders/CreateAnimation.frag.glsl",
				ShaderType::FragmentShader
			},
		};

		Shared<Shader> shader = MakeShared<Shader>(2, infos);
		_animationShader = MakeShared<AnimationShader>(shader);

		for (auto& entity : entities)
		{
			auto& ac = entity.GetComponent<AnimationComponent>();

			ac.shader = _animationShader;
		}
	}

	void CreateAnimation::Play(float progress)
	{
		for (auto& entity : _entities)
		{
			auto& ac = entity.GetComponent<AnimationComponent>();

			if (ac.shader != _animationShader)
			{
				const char* tag = entity.GetComponent<TagComponent>().tag;
				VANIM_WARN("Entity \"" << tag << "\" seems to be playing two animations at the same time");
				continue;
			}

			ac.shader->SetProgress(progress);
		}
	}
}
