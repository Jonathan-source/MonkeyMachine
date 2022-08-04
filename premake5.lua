-- Makes a path relative to the folder containing this script file.
ROOT_PATH = function(path)
    return string.format("%s/%s", _MAIN_SCRIPT_DIR, path)
end

BASE_DIR = ROOT_PATH("")
print("\nBase directory: " .. BASE_DIR)

-----------------------------------------
--	WORKSPACE
-----------------------------------------
workspace ("Workspace")
	architecture "x86_64"
    startproject "Sandbox"
	
	platforms { "Win64" }
	configurations { "Debug", "Release" }
	
	flags { "MultiProcessorCompile" }
	

include "Sandbox/premake5.lua"
include "Engine/premake5.lua"


-- Clean action.
newaction {
	trigger = "clean",
	description = "Remove all binaries, intermediate binaries and visual studio files.",
    execute = function()
        print("Removing binaries")
        os.rmdir("Build/Bin")

        print("Removing intermediate binaries")
        os.rmdir("Build/Intermediate")

        print("Removing project files")
        os.rmdir("Build/Generated")
        os.rmdir("./.vs")
        os.remove("**.sln")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.filters")
        os.remove("**.vcxproj.user")
        print("Done")
    end
}