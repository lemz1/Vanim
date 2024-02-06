#include "editorpch.h"
#include "EditorState.h"

#include "VanimEditor/Rendering/ImGuiStyle.h"

#include "VanimEditor/Script/CameraController.h"

namespace Vanim
{
	void EditorState::Create()
	{
		ImGuiStyle::SetImGuiStyle();

		_scene.CreateEntity("Test");
		_scene.CreateEntity("Test2");

		_sceneHierarchyPanel.SetContext(&_scene);

		ShaderInfo infos[] = {
			ShaderInfo
			{
				"assets/shaders/quad.vert.glsl",
				GL_VERTEX_SHADER
			},
			ShaderInfo
			{
				"assets/shaders/quad.frag.glsl",
				GL_FRAGMENT_SHADER
			}
		};

		_frameBuffer = MakeShared<FrameBuffer>();

		_texture = MakeShared<Texture>(Application::GetWindow()->GetWidth(), Application::GetWindow()->GetHeight());

		_frameBuffer->LinkTexture(GL_COLOR_ATTACHMENT0, *_texture);

		_vertexArray = MakeShared<VertexArray>();

		_shader = MakeShared<Shader>(2, infos);
	}

	void EditorState::Update(const double deltaTime)
	{
		_scene.Update(deltaTime);
	}

	void EditorState::Draw()
	{
		_frameBuffer->Bind();
		_shader->Bind();
		_vertexArray->Bind();
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		_vertexArray->Unbind();
		_shader->Unbind();	
		_frameBuffer->Unbind();
	}

	void EditorState::DrawImGui()
	{
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

		ImGuiWindowFlags sceneFlags = ImGuiWindowFlags_NoCollapse;
		// sceneFlags |= ImGuiWindowFlags_NoMove;

		ImGui::Begin("Scene", nullptr, sceneFlags);

		ImVec2 size = ImGui::GetContentRegionAvail();
		size.y = size.x / (16.f / 9.f);

		ImTextureID textureID = reinterpret_cast<ImTextureID>((GLuint)*_texture);
		ImGui::Image(textureID, size, ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();

		_sceneHierarchyPanel.DrawImGui();
	}

	void EditorState::Destroy()
	{
		_scene.Destroy();
	}
}
