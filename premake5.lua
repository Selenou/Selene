workspace "Selene"
	architecture "x64"

	configurations 
	{ 
		"Debug", 
		"DebugOptimized", 
		"Release" 
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Selene"
	location "Selene"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp" 
	}

	includedirs 
	{ 
		"%{prj.name}/vendor/spdlog/include" 
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
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

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp" 
	}

	includedirs 
	{ 
		"Selene/vendor/spdlog/include", 
		"Selene/src" 
	}

	links 
	{ 
		"Selene" 
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"

		defines 
		{ 
			"SLN_PLATFORM_WINDOWS" 
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