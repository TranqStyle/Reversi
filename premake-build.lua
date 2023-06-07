-- Reference: https://github.com/premake/premake-core/wiki/Tutorial:-Premake-example-with-GLFW-and-OpenGL
workspace "Reversi"
    configurations { "Debug", "Release" }
    location ("Generated/" .. _ACTION)
    language "C++"
    cppdialect "C++17"
    startproject "Server"
    
    if (_ACTION == "gmake") then
        buildoptions { "-Wall -Werror" }
    end
    
    -- Set settings only for the Debug configuration
    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

    -- Set settings only for the Release configuration
    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"

    -- Reset the filter for other settings
    filter { }
    
    targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")
    objdir ("Build/Obj/%{prj.name}/%{cfg.longname}")
    
function buildfile(buildfilePath)
    dofile(buildfilePath .. "/premake-build.lua")
end
function usefile(usefilePath)
    dofile(usefilePath .. "/premake-use.lua")
end

----------
-- Core --
----------
buildfile ("Projects/Core")

function useCore()
    usefile ("Projects/Core")
end

-------------
-- Players --
-------------
-- DefaultPlayers --
buildfile ("Projects/Players/DefaultPlayers")

function useDefaultPlayers()
    usefile ("Projects/Players/DefaultPlayers")
end

-- HumanPlayers --
PLAYERS = { "StackAI", "TranqAI" }

for i,v in ipairs(PLAYERS) do
    buildfile ("Projects/Players/" .. v)
end

function useHumanPlayers()
    for i,v in ipairs(PLAYERS) do
        usefile ("Projects/Players/" .. v)
    end
end

----
function usePlayers()
    useDefaultPlayers()
    useHumanPlayers()
end

------------
-- Server --
------------
buildfile ("Projects/Server")