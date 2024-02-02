project "VanimCore"
    kind "StaticLib"
    language "C"
    cdialect "C17"

    files { "**.h", "**.c" }

    includedirs 
    {
        "src",
        "%{wks.location}/vendor/glfw/glfw/include",
        "%{wks.location}/vendor/glad/glad/include",
        "%{wks.location}/vendor/imgui/imgui"
    }

    links 
    {
        "GLFW"
    }