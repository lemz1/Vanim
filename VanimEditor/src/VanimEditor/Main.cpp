#include <iostream>

#include "VanimCore.h"

#include "VanimCore/NativeScript/CameraController.h"

namespace Vanim
{
	class EditorState : public State
	{
	public:
		void Create() override
		{
			State::Create();


			Entity camera = CreateEntity("Camera");

			camera.AddComponent<TransformComponent>();
			camera.AddComponent<CameraComponent>();
			camera.AddComponent<NativeScriptComponent>().Bind<CameraController>();
		}

		void Update(const double deltaTime) override
		{
			State::Update(deltaTime);
		}
		
		void Destroy() override
		{
			State::Destroy();
		}
	private:
	};
}

int main()
{
	using namespace Vanim;

	WindowSpecification windowSpec;
	windowSpec.title = "Vanim";
	windowSpec.width = 1280;
	windowSpec.height = 720;
	windowSpec.vSync = false;

	ApplicationSpecification spec;
	spec.windowSpec = windowSpec;

	Application* app = new Application(spec, new EditorState());
	app->Run();
	delete app;

	return 0;
}
