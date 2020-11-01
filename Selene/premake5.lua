project "Selene"
	kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "slnpch.h"
	pchsource "src/slnpch.cpp"

	files 
	{
		"src/**.h", 
		"src/**.cpp" 
	}

	includedirs 
	{ 
		"vendor/spdlog/include",
		"%{IncludeDir.Glfw}"
	}
	
	links 
	{ 
		"Glfw",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{ 
			"SLN_PLATFORM_WINDOWS", 
			"SLN_BUILD_DLL" 
		}

		postbuildcommands 
		{ 
			"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game" 
		}

	filter "configurations:Debug"
		defines "SLN_DEBUG"
		symbols "on"

	filter "configurations:DebugOptimized"
		defines "SLN_DEBUGOPT"
		optimize "on"

	filter "configurations:Release"
		defines "SLN_RELEASE"
		optimize "on"