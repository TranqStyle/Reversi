-- StackPlayer --
project "StackPlayer"
    kind "StaticLib"
    
    files { "./StackPlayer/**" }
    
    includedirs "./StackPlayer"
    
    useCore()