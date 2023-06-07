project "Server"
    kind "ConsoleApp"
    
    files { "./**" }
    usePlayers()
    useCore() -- This one is actually unnecessary, as Players use Core
    