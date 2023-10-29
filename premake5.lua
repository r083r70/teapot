workspace "game"
	architecture "x86_64"
	configurations { "Debug", "Release" }
	startproject "game"

include "thirdparty/raylib"

project "game"
	kind "ConsoleApp"

	language "C++"
	cppdialect "C++20"

	targetdir ("bin/%{cfg.buildcfg}")
	objdir ("obj/%{cfg.buildcfg}" )

	includedirs {
		"src/",
		"thirdparty/entt/",
		"thirdparty/raylib/src/"
	}

	links {
		"raylib"
	}

	files {
		"src/**.h",
		"src/**.cpp",
	}

	filter "Debug"
        defines { "CP_DEBUG" }
		symbols "On"

	filter "Release"
        defines { "CP_RELEASE" }
		optimize "On"

	filter "system:linux"
		systemversion "latest"
        links { "pthread", "GL", "m", "dl", "rt", "X11" }
		defines { "CP_LINUX" }