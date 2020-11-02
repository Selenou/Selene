project "Selene"
	kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "slnpch.h"
	pchsource "src/slnpch.cpp"

	files 
	{
		"src/**.h", 
		"src/**.cpp",
		"vendor/stb_image/stb_image.h",
		"vendor/stb_image/stb_image.cpp",
	}

	includedirs 
	{ 
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.Glfw}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.stb_image}"
	}
	
	links 
	{ 
		"Glfw",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{ 
			"SLN_PLATFORM_WINDOWS"
		}

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