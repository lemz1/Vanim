project "VanimEditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

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
        "%{wks.location}/vendor/entt/entt/src"
    }

    links 
    {
        "VanimCore"
    }