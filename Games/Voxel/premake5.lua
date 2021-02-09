project "Voxel"
	kind "ConsoleApp" --WindowedApp
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
		"Selene",
		"%{wks.location}/Selene/vendor/assimp/assimp-vc141-mt.lib"
	}

	filter "system:windows"
		systemversion "latest"
		linkoptions 
		{ 
			--"/ENTRY:mainCRTStartup" -- if WindowedApp
		}
		
		postbuildcommands 
		{
			'{COPY} "./assets" "%{cfg.targetdir}/assets"',
			'{COPY} "%{wks.location}/Selene/vendor/assimp/assimp-vc141-mt.dll" "%{cfg.targetdir}"'
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