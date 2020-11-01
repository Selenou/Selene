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
IncludeDir["Glfw"] = "%{wks.location}/Selene/vendor/glfw/include"
IncludeDir["stb_image"] = "%{wks.location}/Selene/vendor/stb_image"

group "Vendors"
	include "Selene/vendor/GLFW"
group ""

include "Selene"
include "Game"