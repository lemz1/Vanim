project "Glad"
    kind "StaticLib"
    language "C"
    cdialect "C17"

    includedirs { "glad/include" }

    files { "**.h", "**.c" }