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
		camera.AddComponent<TransformComponent>(glm::vec3(0.f, 0.f, 5.f));

		const uint32_t sceneFrameBufferWidth = (uint32_t)((float)Application::GetWindow()->GetWidth() * 1.0f);
		const uint32_t sceneFrameBufferHeight = (uint32_t)((float)Application::GetWindow()->GetHeight() * 1.0f);

		CameraSpecification cameraSpec = {};
		cameraSpec.width = sceneFrameBufferWidth;
		cameraSpec.height = sceneFrameBufferHeight;
		cameraSpec.isOrthographic = true;

		camera.AddComponent<CameraComponent>(cameraSpec);
		//camera.AddComponent<NativeScriptComponent>().Bind<CameraController>();

		auto quad = _scene.CreateEntity("Quad");
		quad.AddComponent<TransformComponent>();

		_sceneHierarchyPanel.SetContext(&_scene);

		_sceneFrameBuffer = MakeUnique<FrameBuffer>();

		_sceneTexture = MakeUnique<Texture>(sceneFrameBufferWidth, sceneFrameBufferHeight);

		_sceneFrameBuffer->LinkTexture(GL_COLOR_ATTACHMENT0, *_sceneTexture);

		GraphSpecification2D graphSpec;
		graphSpec.lineWidth = 5.f;
		graphSpec.color = Color::babyBlue;
		_graph = MakeUnique<Graph2D>(graphSpec);

		_graph->CalculateCoordinates(
			[](float x) -> float
			{
				return 2.0f * x * x - 0.75f;
			}, 
			GraphData2D 
			{
				-1.f,	
				1.f,
				0.05f,
				{ } 
			}
		);
	}

	void EditorState::Update(const float deltaTime)
	{
		_scene.Update(deltaTime);
	}

	void EditorState::Draw()
	{
		_sceneTexture->SetViewport();

		_sceneFrameBuffer->Bind();

		_sceneFrameBuffer->Clear(0.3f, 0.3f, 0.3f, 1.0f);

		CameraComponent cc;
		TransformComponent ctc;
		for (auto& entity : _scene.GetEntitiesOfTypes<TransformComponent, CameraComponent>())
		{
			cc = entity.GetComponent<CameraComponent>();
			ctc = entity.GetComponent<TransformComponent>();

			_renderer->SetViewProjection(ctc.AsMat4(), cc.camera.GetProjection());

			break;
		}

		for (auto& entity : _scene.GetEntitiesOfType<TransformComponent>())
		{
			if (entity.HasAnyOf<CameraComponent>())
			{
				continue;
			}

			auto& tc = entity.GetComponent<TransformComponent>();

			_renderer->DrawQuad(
				tc.AsMat4(),
				glm::vec4(1.0f, 0.5f, 0.5f, 1.0f)
			);
		}

		_graph->Draw();

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
