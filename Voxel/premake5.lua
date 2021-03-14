project "Voxel"
	kind "ConsoleApp"
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
        "%{wks.location}/Selene/src",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.openal}",
		"%{IncludeDir.entt}",
		"./vendor/fastnoise/include"
	}

	links 
	{ 
		"Selene",
		"%{wks.location}/Selene/vendor/assimp/assimp-vc141-mt.lib",
		"%{wks.location}/Selene/vendor/openal/OpenAL32.lib",
		"%{wks.location}/Selene/vendor/vulkan/vulkan-1.lib"
	}

	filter "system:windows"
		systemversion "latest"
		
		links
		{
			"d3d11.lib",
			"dxgi.lib"
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