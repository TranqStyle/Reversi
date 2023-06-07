#!/bin/sh
rm -rf Build
rm -rf Generated
./premake5.exe --cc=gcc --dc=gdc --file=premake-build.lua --os=linux --verbose --fatal gmake
make -C Generated/gmake
./Build/Bin/Server/Debug/Server
