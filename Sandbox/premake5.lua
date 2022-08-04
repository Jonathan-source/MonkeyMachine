-----------------------------------------
--	SANDBOX
-----------------------------------------
project "Sandbox"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	basedir(BASE_DIR)
	location (BASE_DIR .. "Build/Generated")
	buildlog (BASE_DIR .. "Build/Logs/GameBuildLog.log")
	objdir (BASE_DIR .. "Build/Intermediate/%{cfg.platform}_%{cfg.buildcfg}")
	targetdir (BASE_DIR .. "Build/Bin/%{prj.name}/%{cfg.platform}_%{cfg.buildcfg}")
	
	targetname "Sandbox"
	
	pchheader "pch.h"
	pchsource "Source/pch.cpp"

	includedirs { 
		"Source",
		BASE_DIR .. "Engine/Source",
	}

	files { "Source/**.h", "Source/**.cpp" }

	links { "Engine" }

	libdirs {  }

	filter { "platforms:Win64" }
		defines { "WIN32", "_WIN32", "_CRT_SECURE_NO_WARNINGS" }
		systemversion "latest"

	filter { "configurations:Debug" }
		defines { "DEBUG", "_DEBUG" }
		symbols "On"
		optimize "Off"

	filter { "configurations:Release" }
		defines { "NDEBUG", "_UNICODE", "UNICODE" }
		symbols "Off"
		optimize "Speed"