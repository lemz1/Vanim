#include "editorpch.h"
#include "VanimCore.h"

#include "Editor/EditorState.h"

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
