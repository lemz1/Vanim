#include <stdio.h>

#include "VanimCore.h"

int main()
{
	WindowSpecification windowSpec;
	windowSpec.title	= "Vanim";
	windowSpec.width	= 1280;
	windowSpec.height	= 720;
	windowSpec.vSync	= true;

	ApplicationSpecification spec;
	spec.windowSpec = windowSpec;

	createApplication(&spec);
	runApplication();
	endApplication();

	return 0;
}
