project "VanimCore"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    pchheader "corepch.h"
    pchsource "src/corepch.cpp"

    files { "**.h", "**.c", "**.hpp", "**.cpp" }

    includedirs 
    {
        "src",
        "%{wks.location}/vendor/glfw/glfw/include",
        "%{wks.location}/vendor/glad/glad/include",
        "%{wks.location}/vendor/imgui/imgui",
        "%{wks.location}/vendor/glm/glm",
        "%{wks.location}/vendor/entt/entt/src",
        "%{wks.location}/vendor/lua"
    }

    links 
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32",
        "%{wks.location}/vendor/lua/lua542/lua54"
    }