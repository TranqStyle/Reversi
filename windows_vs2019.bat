rm -rf Build
rm -rf Generated
premake5 --cc=gcc --dc=gdc --file=premake-build.lua --os=windows --verbose --fatal vs2019
