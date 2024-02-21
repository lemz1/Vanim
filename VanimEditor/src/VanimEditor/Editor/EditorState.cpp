#include "editorpch.h"
#include "EditorState.h"

#include "VanimEditor/Rendering/ImGuiStyle.h"

#include "VanimEditor/Script/CameraController.h"

#include "VanimEditor/Animation/IAnimation.h"

namespace Vanim
{
	void EditorState::Create()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		ImGuiStyle::SetImGuiStyle();

		ShaderInfo infos[] = {
			ShaderInfo
			{
				"Assets/Shaders/Default.vert.glsl",
				ShaderType::VertexShader
			},
			ShaderInfo
			{
				"Assets/Shaders/Default.frag.glsl",
				ShaderType::FragmentShader
			},
		};

		_defaultShader = MakeShared<Shader>(2, infos);

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

		graph.AddComponent<AnimationComponent>(_defaultShader, gc.graph.GetVAO(), gc.graph.NumIndices());

		_sceneHierarchyPanel.SetContext(&_scene);

		_sceneFrameBuffer = MakeUnique<FrameBuffer>();

		_sceneTexture = MakeUnique<Texture>(sceneFrameBufferWidth, sceneFrameBufferHeight);
		_sceneDepthBuffer = MakeUnique<RenderBuffer>(sceneFrameBufferWidth, sceneFrameBufferHeight);

		_sceneFrameBuffer->LinkTexture(GL_COLOR_ATTACHMENT0, *_sceneTexture);
		_sceneFrameBuffer->LinkRenderBuffer(GL_DEPTH_ATTACHMENT, *_sceneDepthBuffer);

		Application::GetWindow()->SetVSync(false);

		std::vector<Entity> createEntities = { graph };
		_createAnimation = MakeUnique<CreateAnimation>(createEntities);
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

		for (auto& entity : _scene.GetEntitiesOfType<AnimationComponent>())
		{
			auto& ac = entity.GetComponent<AnimationComponent>();
			auto& tc = entity.GetComponent<TransformComponent>();

			ac.color = Color::HSLtoRGB(glm::vec3(fmod(Application::GetTime() * 0.2f, 1.0f), 1.0f, 0.5f));

			ac.shader->SetViewProjection(viewProjection);
			ac.shader->SetModelMatrix(tc.AsMat4());
			ac.shader->SetColor(ac.color);

			Renderer::DrawMesh(ac.shader->GetShader(), ac.GetVAO(), ac.NumIndices());
		}

		_sceneFrameBuffer->Unbind();
	}

	void EditorState::DrawImGui()
	{
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

		ImGuiWindowFlags sceneFlags = ImGuiWindowFlags_NoCollapse;
		// sceneFlags |= ImGuiWindowFlags_NoMove;

		ImGui::Begin("Scene", nullptr, sceneFlags);

		ImVec2 size = ImVec2(_sceneTexture->GetWidth(), _sceneTexture->GetHeight());

		ImTextureID textureID = reinterpret_cast<ImTextureID>((GLuint)*_sceneTexture);
		ImGui::Image(textureID, size, ImVec2(0, 1), ImVec2(1, 0));
		
		ImGui::End();

		ImGui::Begin("Animator");
		ImGui::Text("Animation");
		ImGui::End();

		_sceneHierarchyPanel.DrawImGui();

		if (_showDebugInfo)
		{
			ImGui::Begin("DebugInfo");
			ImGui::Text("%d FPS", (int32_t)ImGui::GetIO().Framerate);
			ImGui::Text("Entities: %d", _scene.GetEntitiesOfTypes<entt::entity>().size());
			ImGui::End();
		}
	}

	void EditorState::Destroy()
	{
		_scene.Destroy();
	}
}
