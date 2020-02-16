#Removing and recreating build directory
rm -r "$PSScriptRoot/build"
mkdir build > $null

#Invoking cmake for build directory
cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build -G "MinGW Makefiles"