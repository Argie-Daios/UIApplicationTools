workspace "UIApplicationTools"
	architecture "x64"
	startproject "TicTacToe"

	configurations
	{
		"Debug",
		"Release"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["SDL2"] = "UIApplicationTools/vendor/SDL2/include";
	IncludeDir["SDL2_mixer"] = "UIApplicationTools/vendor/SDL2_mixer/include";
	IncludeDir["SDL2_ttf"] = "UIApplicationTools/vendor/SDL_ttf/include";
	IncludeDir["glm"] = "UIApplicationTools/vendor/glm";

	LibraryDir = {}
	LibraryDir["SDL2"] = "UIApplicationTools/vendor/SDL2/lib/x64/SDL2.lib";
	LibraryDir["SDL2main"] = "UIApplicationTools/vendor/SDL2/lib/x64/SDL2main.lib";
	LibraryDir["SDL2image"] = "UIApplicationTools/vendor/SDL2/lib/x64/SDL2_image.lib";
	LibraryDir["SDL2mixer"] = "UIApplicationTools/vendor/SDL2_mixer/lib/x64/SDL2_mixer.lib";
	LibraryDir["SDL2ttf"] = "UIApplicationTools/vendor/SDL2_ttf/lib/x64/SDL2_ttf.lib";

project "UIApplicationTools"
	location "UIApplicationTools"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir  ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",

		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",

		"%{IncludeDir.SDL2}",
		"%{IncludeDir.SDL2_mixer}",
		"%{IncludeDir.SDL2_ttf}",
		"%{IncludeDir.glm}"
	}

	libdirs
	{
		"%{prj.name}/vendor/SDL2/lib/x64",
		"%{prj.name}/vendor/SDL2_mixer/lib/x64",
		"%{prj.name}/vendor/SDL_ttf/lib/x64"
	}

	links
	{
		"SDL2.lib",
		"SDL2main.lib",
		"SDL2_image.lib",
		"SDL2_mixer.lib",
		"SDL2_ttf.lib",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"UIWINDOWS"
		}

	filter "configurations:Debug"
		defines "UIDEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "UIRELEASE"
		runtime "Release"
		optimize "On"

project "Application"
	location "Application"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir  ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"UIApplicationTools/src",
		"%{prj.name}/src",
		"%{IncludeDir.glm}"
	}

	links
    {
        "UIApplicationTools"
    }

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"UIWINDOWS"
		}

	filter "configurations:Debug"
		defines "UIDEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "UIRELEASE"
		runtime "Release"
		optimize "On"

project "TicTacToe"
	location "TicTacToe"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir  ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"UIApplicationTools/src",
		"%{prj.name}/src",
		"%{IncludeDir.glm}"
	}

	links
    {
        "UIApplicationTools"
    }

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"UIWINDOWS"
		}

	filter "configurations:Debug"
		defines "UIDEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "UIRELEASE"
		runtime "Release"
		optimize "On"