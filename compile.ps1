#Remove outdated binary
rm -ErrorAction Ignore "$PSScriptRoot\bin\run.exe" 

#Calling make for build directory
cd "$PSScriptRoot\build"; mingw32-make; cd ".."