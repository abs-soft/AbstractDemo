/*
Copyright 2023 Abstract Software, Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the “Software”), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "AbstractAccessibleConfigManager.h"
// #include "GeneratorDefine.h"
#include "ProjectDescriptor.h"
#include "CoreUObject.h"
#include "Misc/FileHelper.h"
// #include "UObjectIterator.h"
#include "Serialization/JsonSerializer.h"

// ERROR: FLuaConfigManager

void FAbstractAccessibleConfigManager::Init()
{
    ProjectPath.Empty();
    GameModuleName.Empty();

    FString ProjectFilePath = FPaths::GetProjectFilePath();
    ProjectPath = FPaths::GetPath(ProjectFilePath);
    AbstractAccessibleConfigFileRelativePath = FString("Config/AbstractAccessible/GeneratorConfig.ini");
    FString ConfigFilePath = ProjectPath / AbstractAccessibleConfigFileRelativePath;

    GConfig->GetArray(TEXT("SupportModules"), TEXT("ModuleName"), SupportedModules, ConfigFilePath);

    // if (!FPaths::IsProjectFilePathSet())
    // {
    //     DebugLog(TEXT("Project file path not set!"));
    // }

    FText OutError;
    FProjectDescriptor ProjectDescriptor;

    // FPaths::GetProjectFilePath() return the  path of project's .uproject file
    ProjectDescriptor.Load(ProjectFilePath, OutError);

    // init the GameModuleName by the first module name in the file of ProjectName.uproject 
    ProjectDescriptor.Modules[0].Name.ToString(GameModuleName);
}
