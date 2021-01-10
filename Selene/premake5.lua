project "Selene"
	kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "slnpch.h"
	pchsource "src/slnpch.cpp"
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	files 
	{
		"src/**.h", 
		"src/**.cpp",
		"vendor/stb_image/**.cpp"
	}

	includedirs 
	{ 
		"src",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.vulkan}"
	}
	
	links 
	{ 
		"Glfw",
		"Glad",
		"ImGui",
		"vendor/vulkan/vulkan-1.lib" -- defined opengl32.lib
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "SLN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:DebugOptimized"
		defines "SLN_DEBUGOPT"
		runtime "Release"
		optimize "on"

	filter "configurations:Release"
		defines "SLN_RELEASE"
		runtime "Release"
		optimize "on"