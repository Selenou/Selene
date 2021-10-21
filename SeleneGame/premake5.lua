project "SeleneGame"
	kind "ConsoleApp" --WindowedApp
    language "C++"
    cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/int/" .. outputdir .. "/%{prj.name}")

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
		"src",
        "%{wks.location}/Selene/src",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.openal}",
		"%{IncludeDir.entt}",
		"./vendor/tileson/include"
	}

	links 
	{ 
		"Selene",
		"%{wks.location}/Selene/vendor/assimp/assimp-vc141-mt.lib",
		"%{wks.location}/Selene/vendor/openal/OpenAL32.lib"
	}

	filter "system:windows"
		systemversion "latest"
		
		linkoptions 
		{ 
			--"/ENTRY:mainCRTStartup"
		}
		
		postbuildcommands 
		{
			'{COPY} "./assets" "%{cfg.targetdir}/assets"',
			'{COPY} "%{wks.location}/Selene/vendor/assimp/assimp-vc141-mt.dll" "%{cfg.targetdir}"',
			'{COPY} "%{wks.location}/Selene/vendor/openal/OpenAL32.dll" "%{cfg.targetdir}"'
		}

	filter "configurations:Debug"
		defines "SLN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SLN_RELEASE"
		runtime "Release"
		optimize "on"