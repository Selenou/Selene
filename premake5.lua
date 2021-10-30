workspace "Selene"
	architecture "x86_64"
	startproject "SeleneGame"

	configurations 
	{ 
		"Debug", 
		"Release" 
	}
	
	flags
    {
        "MultiProcessorCompile"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glfw"] = "%{wks.location}/Selene/vendor/glfw/include"
IncludeDir["glad"] = "%{wks.location}/Selene/vendor/glad/include"
IncludeDir["glm"] = "%{wks.location}/Selene/vendor/glm/include"
IncludeDir["stb_image"] = "%{wks.location}/Selene/vendor/stb_image/include"
IncludeDir["imgui"] = "%{wks.location}/Selene/vendor/imgui"
IncludeDir["openal"] = "%{wks.location}/Selene/vendor/openal/include"
IncludeDir["assimp"] = "%{wks.location}/Selene/vendor/assimp/include"
IncludeDir["entt"] = "%{wks.location}/Selene/vendor/entt/include"

group "Dependencies"
	include "Selene/vendor/glfw"
	include "Selene/vendor/glad"
	include "Selene/vendor/imgui"
group ""

include "Selene"
include "SeleneGame"

newaction 
{
	trigger     = "clean",
	description = "Clean build files",
	execute     = function ()
		print("Cleaning build files ...")
		os.remove{"**.sln", "**.vcxproj", "**.vcxproj.filters", "**.vcxproj.user"}
		print("Cleaning project binaries ...")
		os.rmdir("./bin")
		os.rmdir("./bin-int")
		print("Cleaning vendor binaries ...")
		-- Glad
		os.rmdir("./Selene/vendor/glad/bin")
		os.rmdir("./Selene/vendor/glad/bin-int")
		-- Glfw
		os.rmdir("./Selene/vendor/glfw/bin")
		os.rmdir("./Selene/vendor/glfw/bin-int")
		-- Imgui
		os.rmdir("./Selene/vendor/imgui/bin")
		os.rmdir("./Selene/vendor/imgui/bin-int")
		print("Cleaning done !")
	end
}