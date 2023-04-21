@echo off

for /f "usebackq delims=" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -prerelease -products * -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe`) do set MSBUILD_PATH=%%i

"%MSBUILD_PATH%" "%CD%/vs3.sln" /t:Clean
