#include <stdio.h>

#include "VanimCore.h"

using namespace Vanim;

int main()
{
	WindowSpecification windowSpec;
	windowSpec.title	= "Vanim";
	windowSpec.width	= 1280;
	windowSpec.height	= 720;
	windowSpec.vSync	= true;

	ApplicationSpecification spec;
	spec.windowSpec = windowSpec;

	Application* app = new Application(spec);
	app->Run();
	delete app;

	return 0;
}
