#include "editorpch.h"
#include "EditorState.h"

#include "VanimEditor/Rendering/ImGuiStyle.h"

#include "VanimEditor/Script/CameraController.h"

namespace Vanim
{
	void EditorState::Create()
	{
		ImGuiStyle::SetImGuiStyle();

		_renderer = MakeUnique<Renderer>();

		auto camera = _scene.CreateEntity("Camera");
		camera.AddComponent<TransformComponent>();
		camera.AddComponent<CameraComponent>().camera.SetOrthographic(true);

		auto quad = _scene.CreateEntity("Quad");
		quad.AddComponent<TransformComponent>();

		_sceneHierarchyPanel.SetContext(&_scene);

		_sceneFrameBuffer = MakeUnique<FrameBuffer>();

		_sceneTexture = MakeUnique<Texture>(Application::GetWindow()->GetWidth(), Application::GetWindow()->GetHeight());

		_sceneFrameBuffer->LinkTexture(GL_COLOR_ATTACHMENT0, *_sceneTexture);
	}

	void EditorState::Update(const double deltaTime)
	{
		_scene.Update(deltaTime);
	}

	void EditorState::Draw()
	{
		_sceneFrameBuffer->Bind();

		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		CameraComponent cc;
		TransformComponent ctc;
		for (auto& entity : _scene.GetEntitiesOfTypes<TransformComponent, CameraComponent>())
		{
			cc = entity.GetComponent<CameraComponent>();
			ctc = entity.GetComponent<TransformComponent>();

			break;
		}

		for (auto& entity : _scene.GetEntitiesOfType<TransformComponent>())
		{
			if (entity.HasAnyOf<CameraComponent>())
			{
				continue;
			}

			auto& tc = entity.GetComponent<TransformComponent>();
			tc.transform[3][2] = -0.1f;

			_renderer->DrawQuad(
				tc.transform,
				ctc.transform,
				cc.camera.GetProjection(),
				glm::vec4(1.0f, 0.5f, 0.5f, 1.0f)
			);
		}

		_sceneFrameBuffer->Unbind();
	}

	void EditorState::DrawImGui()
	{
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

		ImGuiWindowFlags sceneFlags = ImGuiWindowFlags_NoCollapse;
		// sceneFlags |= ImGuiWindowFlags_NoMove;

		ImGui::Begin("Scene", nullptr, sceneFlags);

		ImVec2 size = ImGui::GetContentRegionAvail();

		if (size.x / (16.f / 9.f) < size.y)
		{
			size.y = size.x / (16.f / 9.f);
		}
		else
		{
			size.x = size.y * (16.f / 9.f);
		}

		ImTextureID textureID = reinterpret_cast<ImTextureID>((GLuint)*_sceneTexture);
		ImGui::Image(textureID, size, ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();

		ImGui::Begin("Animator");
		ImGui::Text("Animation");
		ImGui::End();

		_sceneHierarchyPanel.DrawImGui();
	}

	void EditorState::Destroy()
	{
		_scene.Destroy();
	}
}
