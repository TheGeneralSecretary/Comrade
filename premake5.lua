include "Dependencies.lua"

workspace "Comrade"
   architecture "x86"
   startproject "Comrade"
   configurations { "Debug", "Release" }

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

group "Dependencies"
   include "Comrade/Dependencies/spdlog"
   include "Comrade/Dependencies/glfw"
   include "Comrade/Dependencies/glad"
   include "Comrade/Dependencies/imgui"
   include "Comrade/Dependencies/yaml-cpp"
group ""

include "Comrade"
