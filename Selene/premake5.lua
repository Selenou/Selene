project "Selene"
	kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/int/" .. outputdir .. "/%{prj.name}")
	
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
		"vendor/stb_image/stb_image.cpp",
		"vendor/ImGui/imgui_build.cpp"
	}

	includedirs 
	{ 
		"src",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.openal}",
		"%{IncludeDir.vulkan}",
		"%{IncludeDir.assimp}",
		"%{IncludeDir.entt}"
	}
	
	links 
	{ 
		"Glfw",
		"Glad",
		"ImGui"
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