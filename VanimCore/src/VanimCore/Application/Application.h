#pragma once

#include <stdio.h>

#include "VanimCore/Window/Window.h"

typedef struct
{
	WindowSpecification windowSpec;
} ApplicationSpecification;

Window	g_Window;
bool	g_IsRunning;

void createApplication(ApplicationSpecification* spec);

void runApplication();

void endApplication();