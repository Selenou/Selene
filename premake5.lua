workspace "Selene"
	architecture "x86_64"
	startproject "Game"

	configurations 
	{ 
		"Debug", 
		"DebugOptimized", 
		"Release" 
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glfw"] = "%{wks.location}/Selene/vendor/glfw/include"
IncludeDir["glad"] = "%{wks.location}/Selene/vendor/glad/include"
IncludeDir["spdlog"] = "%{wks.location}/Selene/vendor/spdlog"
IncludeDir["glm"] = "%{wks.location}/Selene/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Selene/vendor/stb_image"

group "Vendors"
	include "Selene/vendor/glfw"
	include "Selene/vendor/glad"
group ""

include "Selene"
include "Game"