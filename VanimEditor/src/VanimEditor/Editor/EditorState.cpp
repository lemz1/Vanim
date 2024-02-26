#include "editorpch.h"
#include "EditorState.h"

#include "VanimEditor/Rendering/MyGui.h"

#include "VanimEditor/Script/CameraController.h"

namespace Vanim
{
	void EditorState::Create()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		MyGui::SetImGuiStyle();

		_animationManager = MakeShared<AnimationManager>();

		auto camera = _scene.CreateEntity("Camera");
		camera.AddComponent<TransformComponent>(glm::vec3(0.f, 0.f, 5.f));

		const uint32_t sceneFrameBufferWidth = (uint32_t)((float)Application::GetWindow()->GetWidth() * 0.5f);
		const uint32_t sceneFrameBufferHeight = (uint32_t)((float)Application::GetWindow()->GetHeight() * 0.5f);

		CameraSpecification cameraSpec = {};
		cameraSpec.width = sceneFrameBufferWidth;
		cameraSpec.height = sceneFrameBufferHeight;
		cameraSpec.isOrthographic = true;
		cameraSpec.orthographicSize = 9.0f;

		camera.AddComponent<CameraComponent>(Camera(cameraSpec));
		//camera.AddComponent<NativeScriptComponent>().Bind<CameraController>();

		auto graph = _scene.CreateEntity("Graph");
		graph.AddComponent<TransformComponent>(glm::vec3(0.0f, 0.0f, 0.1f)); // moving it a bit so that it is rendered infront of the quad

		auto& gc = graph.AddComponent<GraphComponent>(10.0f);

		gc.graph.CalculateCoordinates(
			[](float x) -> float
			{
				return Math::Sin(x);
			},
			GraphData
			{
				Rect 
				{
					-8.0f, 8.0f,
					-4.5f, 4.5f
				},
				0.05f,
				{ }
			}
		);

		_defaultShader = MakeShared<RenderShader>("Assets/Shaders/Default.vert", "Assets/Shaders/Default.frag");

		graph.AddComponent<RenderingComponent>(_defaultShader, gc.graph.GetVAO(), gc.graph.NumIndices());

		_sceneHierarchyPanel = MakeUnique<SceneHierarchyPanel>(&_scene);
		_animatorPanel = MakeUnique<AnimatorPanel>(&_scene, _animationManager.get());

		_sceneFrameBuffer = MakeUnique<FrameBuffer>();

		_sceneTexture = MakeUnique<Texture>(sceneFrameBufferWidth, sceneFrameBufferHeight);
		_sceneDepthBuffer = MakeUnique<RenderBuffer>(sceneFrameBufferWidth, sceneFrameBufferHeight);

		_sceneFrameBuffer->LinkTexture(GL_COLOR_ATTACHMENT0, *_sceneTexture);
		_sceneFrameBuffer->LinkRenderBuffer(GL_DEPTH_ATTACHMENT, *_sceneDepthBuffer);

		Application::GetWindow()->SetVSync(false);
		
		std::vector<Entity> e = { graph };
		_createAnimation = MakeUnique<Animation>("Assets/Data/Animations/Create.frag", e);
	}

	void EditorState::Update(const float deltaTime)
	{
		_scene.Update(deltaTime);

		if (Input::JustPressedKey(Key::F3))
		{
			_showDebugInfo = !_showDebugInfo;
		}

		float progress = Math::Min(Application::GetTime() / 3.0f, 1.0f);
		
		_createAnimation->Play(Ease::OutBounce(Ease::InCubic(progress)));
	}

	void EditorState::Draw()
	{
		_sceneTexture->SetViewport();

		_sceneFrameBuffer->Bind();

		_sceneFrameBuffer->Clear(0.0f, 0.0f, 0.0f, 1.0f);

		glm::mat4 viewProjection{ 1.f };
		for (auto& entity : _scene.GetEntitiesOfTypes<TransformComponent, CameraComponent>())
		{
			auto& projection = entity.GetComponent<CameraComponent>().camera.GetProjection();
			auto& view = entity.GetComponent<TransformComponent>().AsMat4();

			viewProjection = projection * glm::inverse(view);

			break;
		}

		for (auto& entity : _scene.GetEntitiesOfType<RenderingComponent>())
		{
			auto& rc = entity.GetComponent<RenderingComponent>();
			auto& tc = entity.GetComponent<TransformComponent>();

			glm::vec4 color = Color::HSLtoRGB(glm::vec3(fmod(Application::GetTime() * 0.2f, 1.0f), 1.0f, 0.5f));

			rc.shader->GetShader()->Bind();

			rc.shader->GetShader()->Set4x4Matrix(rc.shader->GetViewProjectionID(), 1, false, (GLfloat*)&viewProjection);
			rc.shader->GetShader()->Set4x4Matrix(rc.shader->GetModelMatrixID(), 1, false, (GLfloat*)&tc.AsMat4());
			rc.shader->GetShader()->SetFloats(rc.shader->GetColorID(), color.r, color.g, color.b, color.a);

			rc.shader->GetShader()->Unbind();

			Renderer::DrawMesh(rc.shader->GetShader(), rc.GetVAO(), rc.NumIndices());
		}

		_sceneFrameBuffer->Unbind();
	}

	void EditorState::DrawImGui()
	{
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

		{
			ImGui::Begin("Scene", nullptr, MyGui::defaultWindowFlags);

			ImVec2 size = ImVec2(_sceneTexture->GetWidth(), _sceneTexture->GetHeight());

			ImTextureID textureID = reinterpret_cast<ImTextureID>((GLuint)*_sceneTexture);
			ImGui::Image(textureID, size, ImVec2(0, 1), ImVec2(1, 0));

			ImGui::End();
		}

		{
			_sceneHierarchyPanel->DrawImGui();
		}

		{
			_animatorPanel->DrawImGui();
		}

		{
			ImGui::Begin("Info", nullptr, MyGui::defaultWindowFlags);
			ImGui::Text("F3 - Show Debug Info");

			if (_showDebugInfo)
			{
				ImGui::NewLine();
				ImGui::Text("%d FPS", (uint32_t)ImGui::GetIO().Framerate);
				ImGui::Text("Entities: %d", _scene.GetEntitiesOfTypes<entt::entity>().size());
			}

			ImGui::End();
		}
	}

	void EditorState::Destroy()
	{
		_scene.Destroy();
	}
}
