workspace "Vanim"
    architecture "x64"
    startproject "VanimEditor"
    configurations { "Debug", "Release" }

    targetdir("%{wks.location}/export/%{cfg.system}/%{cfg.buildcfg}/libs/%{prj.name}")
    objdir("%{wks.location}/export/%{cfg.system}/%{cfg.buildcfg}/objs/%{prj.name}")

    defines { "GLM_ENABLE_EXPERIMENTAL" }

    filter "configurations:Debug"
        defines { "VANIM_DEBUG" }
        runtime "Debug"
        optimize "Off"
        symbols "On"

    filter "configurations:Release"
        defines { "VANIM_RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "Off"

    filter "system:windows"
		defines { "VANIM_WINDOWS" }

	filter "system:linux"
		defines { "VANIM_LINUX" }

    filter {}

group "Dependencies"
    include "vendor/glfw"
    include "vendor/glad"
    include "vendor/imgui"
group ""

group "Core"
    include "VanimCore"
group ""

include "VanimEditor"
