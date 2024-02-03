project "VanimCore"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    pchheader "vanimpch.h"
    pchsource "src/vanimpch.cpp"

    files { "**.h", "**.c", "**.hpp", "**.cpp" }

    includedirs 
    {
        "src",
        "%{wks.location}/vendor/glfw/glfw/include",
        "%{wks.location}/vendor/glad/glad/include",
        "%{wks.location}/vendor/imgui/imgui",
        "%{wks.location}/vendor/glm/glm",
        "%{wks.location}/vendor/entt/entt/src"
    }

    links 
    {
        "GLFW",
        "Glad",
        "opengl32.lib"
    }