project "Comrade"
kind "StaticLib"
language "C++"
cppdialect "C++17"
staticruntime "off"

targetdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}")
objdir ("%{wks.location}/build/intermediates/" .. outputdir .. "/%{prj.name}")

pchheader "comradepch.h"
pchsource "Source/comradepch.cpp"

files
{
	"Source/**.h",
	"Source/**.cpp",
	
	"Dependencies/glm/glm/**.hpp",
	"Dependencies/glm/glm/**.inl",
	"Dependencies/stb/**.h",
	"Dependencies/stb/**.cpp",
	"Dependencies/ImGuizmo/ImGuizmo.h",
	"Dependencies/ImGuizmo/ImGuizmo.cpp",
}

excludes "Source/Comrade/Platform/**.cpp"

defines
{
	"COMRADE_ENGINE",
	"GLFW_INCLUDE_NONE",
}

includedirs
{
	"Source",
	"%{IncludeDir.spdlog}",
	"%{IncludeDir.glfw}",
	"%{IncludeDir.glad}",
	"%{IncludeDir.glm}",
	"%{IncludeDir.stb}",
	"%{IncludeDir.imgui}",
	"%{IncludeDir.entt}",
	"%{IncludeDir.yaml_cpp}",
	"%{IncludeDir.imguizmo}",
}

links
{
	"spdlog",
	"glfw",
	"glad",
	"imgui",
	"yaml-cpp",
	"opengl32.lib",
}

filter "files:Dependencies/ImGuizmo/**.cpp"
	flags { "NoPCH" }

filter "system:windows"
	systemversion "latest"

	defines
	{
		"COMRADE_PLATFORM_WINDOWS",
	}

	files
	{
		"Source/Comrade/Platform/Win32/**.cpp"
	}

filter "configurations:Debug"
	defines "COMRADE_DEBUG"
	runtime "Debug"
	symbols "On"

filter "configurations:Release"
	defines "COMRADE_RELEASE"
	runtime "Release"
	optimize "On"
