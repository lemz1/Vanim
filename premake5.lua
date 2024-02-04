workspace "Vanim"
    architecture "x64"
    startproject "VanimEditor"
    configurations { "Debug", "Release" }

    targetdir("%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
    objdir("%{wks.location}/bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")

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
