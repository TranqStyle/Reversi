rm -rf Build
rm -rf Generated
premake5 --cc=gcc --dc=gdc --file=premake-build.lua --os=windows --verbose --fatal gmake
mingw32-make -C Generated/gmake
Build\Bin\Server\Debug\Server.exe