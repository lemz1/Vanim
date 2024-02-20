#include "editorpch.h"
#include "EditorState.h"

#include "VanimEditor/Rendering/ImGuiStyle.h"

#include "VanimEditor/Script/CameraController.h"

namespace Vanim
{
	void EditorState::Create()
	{
		ImGuiStyle::SetImGuiStyle();

		ShaderInfo infos[] = {
			ShaderInfo
			{
				"Assets/Shaders/default.vert.glsl",
				ShaderType::VertexShader
			},
			ShaderInfo
			{
				"Assets/Shaders/default.frag.glsl",
				ShaderType::FragmentShader
			},
		};

		_animationShader = MakeShared<Shader>(2, infos);

		auto camera = _scene.CreateEntity("Camera");
		camera.AddComponent<TransformComponent>(glm::vec3(0.f, 0.f, 5.f));

		const uint32_t sceneFrameBufferWidth = (uint32_t)((float)Application::GetWindow()->GetWidth() * 1.0f);
		const uint32_t sceneFrameBufferHeight = (uint32_t)((float)Application::GetWindow()->GetHeight() * 1.0f);

		CameraSpecification cameraSpec = {};
		cameraSpec.width = sceneFrameBufferWidth;
		cameraSpec.height = sceneFrameBufferHeight;
		cameraSpec.isOrthographic = true;
		cameraSpec.orthographicSize = 9.0f;

		camera.AddComponent<CameraComponent>(Camera(cameraSpec));
		//camera.AddComponent<NativeScriptComponent>().Bind<CameraController>();

		auto graph = _scene.CreateEntity("Graph");
		graph.AddComponent<TransformComponent>(glm::vec3(0.0f, 0.0f, 0.1f)); // moving it a bit so that it is rendered infront of the quad

		GraphSpecification graphSpec;
		graphSpec.lineWidth = 5.f;
		graphSpec.color = Color::emeraldGreen;
		auto& gc = graph.AddComponent<GraphComponent>(graphSpec);

		gc.graph.CalculateCoordinates(
			[](float x) -> float
			{
				return Math::Sin(x);
			},
			GraphData
			{
				-8.0f,
				8.0f,
				0.05f,
				{ }
			}
		);

		graph.AddComponent<AnimationComponent>(_animationShader, gc.graph.GetVAO(), gc.graph.NumIndices());

		_sceneHierarchyPanel.SetContext(&_scene);

		glEnable(GL_DEPTH_TEST);

		_sceneFrameBuffer = MakeUnique<FrameBuffer>();

		_sceneTexture = MakeUnique<Texture>(sceneFrameBufferWidth, sceneFrameBufferHeight);
		_sceneDepthBuffer = MakeUnique<RenderBuffer>(sceneFrameBufferWidth, sceneFrameBufferHeight);

		_sceneFrameBuffer->LinkTexture(GL_COLOR_ATTACHMENT0, *_sceneTexture);
		_sceneFrameBuffer->LinkRenderBuffer(GL_DEPTH_ATTACHMENT, *_sceneDepthBuffer);

		Application::GetWindow()->SetVSync(false);
	}

	void EditorState::Update(const float deltaTime)
	{
		_scene.Update(deltaTime);

		if (Input::JustPressedKey(Key::F3))
		{
			_showDebugInfo = !_showDebugInfo;
		}
	}

	void EditorState::Draw()
	{
		_sceneTexture->SetViewport();

		_sceneFrameBuffer->Bind();

		_sceneFrameBuffer->Clear(0.3f, 0.3f, 0.3f, 1.0f);

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

			ac.shader.SetColor(ac.color);
			ac.shader.SetViewProjection(viewProjection);
			ac.shader.SetModelMatrix(tc.AsMat4());

			Renderer::DrawMesh(ac.shader, ac.GetVAO(), ac.NumIndices());
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
