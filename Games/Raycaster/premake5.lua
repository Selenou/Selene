project "Raycaster"
	kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	files 
	{ 
		"src/**.h", 
		"src/**.cpp" 
	}

	includedirs 
	{ 
        "%{wks.location}/Selene/src",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}"
	}

	links 
	{ 
		"Selene" 
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