project "ComradeEditor"
kind "ConsoleApp"
language "C++"
cppdialect "C++17"
staticruntime "off"

targetdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}")
objdir ("%{wks.location}/build/intermediates/" .. outputdir .. "/%{prj.name}")

files
{
	"Source/**.h",
	"Source/**.cpp",
}

includedirs
{
	"%{wks.location}/Comrade/Source",
	"%{IncludeDir.spdlog}",
	"%{IncludeDir.imgui}",
	"%{IncludeDir.glm}",
	"%{IncludeDir.entt}",
}

links
{
	"Comrade"
}

filter "system:windows"
	systemversion "latest"

filter "configurations:Debug"
	defines "COMRADE_DEBUG"
	runtime "Debug"
	symbols "On"

filter "configurations:Release"
	defines "COMRADE_RELEASE"
	runtime "Release"
	optimize "On"
