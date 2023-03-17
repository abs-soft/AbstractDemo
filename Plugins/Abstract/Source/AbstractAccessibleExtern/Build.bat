
for /f "usebackq delims=" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -prerelease -products * -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe`) do set MSBUILD_PATH=%%i

set targetAASolution="%CD%\Source\AbstractAccessible.sln"

"%MSBUILD_PATH%" %targetAASolution% /p:configuration=debug /p:platform=x64
