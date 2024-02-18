#include "corepch.h"
#include "Application.h"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include "VanimCore/Input/Input.h"

namespace Vanim
{
	Application* Application::_instance = nullptr;

	Application::Application(
		const ApplicationSpecification& spec,
		State* initialState
	)
	{
		if (_instance)
		{
			return;
		}

		_instance = this;

		_window = new Window(spec.windowSpec);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		ImGui_ImplGlfw_InitForOpenGL(_window->_handle, true);
		ImGui_ImplOpenGL3_Init("#version 460 core");
		ImGui::StyleColorsDark();

		_state = initialState;
		_state->Create();
	}

	Application::~Application()
	{
		_state->Destroy();
		delete _state;

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		delete _window;
	}

	void Application::Run()
	{
		_isRunning = true;

		while (!glfwWindowShouldClose(_window->_handle))
		{
			glfwPollEvents();

			Input::UpdateStates();

			const float time = static_cast<float>(glfwGetTime());
			const float deltaTime = time - _time;
			_time = time;

			_state->Update(deltaTime);

			_state->Draw();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			_state->DrawImGui();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(_window->_handle);
		}

		_isRunning = false;
	}

	void Application::SwitchState(
		State* state
	)
	{
		_instance->_state->Destroy();
		delete _instance->_state;
		_instance->_state = state;
		_instance->_state->Create();
	}
}
