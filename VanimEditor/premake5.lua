project "VanimEditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir("%{wks.location}/export/%{cfg.system}/%{cfg.buildcfg}/bin")

    pchheader "editorpch.h"
    pchsource "src/editorpch.cpp"

    files { "**.h", "**.c", "**.hpp", "**.cpp" }

    includedirs 
    {
        "src",
        "%{wks.location}/VanimCore/src",
        "%{wks.location}/vendor/glfw/glfw/include",
        "%{wks.location}/vendor/glad/glad/include",
        "%{wks.location}/vendor/imgui/imgui",
        "%{wks.location}/vendor/glm/glm",
        "%{wks.location}/vendor/entt/entt/src",
        "%{wks.location}/vendor/lua"
    }

    links 
    {
        "VanimCore"
    }

    postbuildcommands 
    {
        "{COPY} \"%{prj.location}Assets\" \"%{cfg.targetdir}\\Assets\"",
        "{COPY} \"%{prj.location}*.dll\" \"%{cfg.targetdir}\"",
        "{COPY} \"%{prj.location}imgui.ini\" \"%{cfg.targetdir}\"",
    }