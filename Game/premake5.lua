project "Game"
	kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{ 
		"src/**.h", 
		"src/**.cpp" 
	}

	includedirs 
	{ 
        "%{wks.location}/Selene/src",
		"%{wks.location}/Selene/vendor/spdlog/include"
	}

	links 
	{ 
		"Selene" 
	}

	filter "system:windows"
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