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

#include "AbstractAccessibleGenerator.h"
// AbstractAccessibleGenerator.h
// #include "GeneratorDefine.h"
#include "ProjectDescriptor.h"
#include "Features/IModularFeatures.h"
#include "Misc/FileHelper.h"
// #include "UObjectIterator.h"
// #include "ConfigClassGenerator.h"
#include "Misc/Paths.h"
#include <cstdlib>
#include <filesystem>
#include "HAL/PlatformProcess.h"
#include "AbstractAccessibleGeneratorGlobal.h"

#define LOCTEXT_NAMESPACE "FAbsPluginModule"

namespace
{
	FString resultBLAH = "";
	void Log(FString line)
	{
		resultBLAH += line + "\n";
	}

	void SetWorkingDirectory(const FString& Directory)
	{
		std::filesystem::current_path(TCHAR_TO_ANSI(*Directory));
	}
}

void FAbstractAccessibleGenerator::StartupModule()
{
	FAbstractAccessibleGeneratorGlobal::GetConfig().Init();
	Log("START UP");
	Log("");
	IModularFeatures::Get().RegisterModularFeature(TEXT("ScriptGenerator"), this);
}

void FAbstractAccessibleGenerator::ShutdownModule()
{
	Log("SHUT DOWN");
	Log("");
	IModularFeatures::Get().UnregisterModularFeature(TEXT("ScriptGenerator"), this);
}

FString FAbstractAccessibleGenerator::GetGeneratedCodeModuleName() const
{
	Log("GET Gen Code Module: " + FAbstractAccessibleGeneratorGlobal::GetConfig().GameModuleName);
	Log("");
	return FAbstractAccessibleGeneratorGlobal::GetConfig().GameModuleName;
}

bool FAbstractAccessibleGenerator::ShouldExportClassesForModule(const FString& ModuleName, EBuildModuleType::Type ModuleType, const FString& ModuleGeneratedIncludeDirectory) const
{
	Log("ModuleName: " + ModuleName);
	Log("Module Gen Inc Dir" + ModuleGeneratedIncludeDirectory);
	Log("");
	return FAbstractAccessibleGeneratorGlobal::GetConfig().SupportedModules.Contains(ModuleName);
}

bool FAbstractAccessibleGenerator::SupportsTarget(const FString& TargetName) const
{
	Log("Target Name: " + TargetName);
	Log("");
	// return m_internal.Config.ProjectPath.IsEmpty() && m_internal.Config.GameModuleName.IsEmpty();
	return true;
}

void FAbstractAccessibleGenerator::Initialize(const FString& RootLocalPath, const FString& RootBuildPath, const FString& OutputDirectory, const FString& IncludeBase)
{
	Log("Root Local: " + RootLocalPath);
	Log("Root Build: " + RootBuildPath);
	Log("Output Dir: " + OutputDirectory);
	Log("Inc Base: " + IncludeBase);
	Log("");

	FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().Initialize(RootLocalPath, RootBuildPath, OutputDirectory, IncludeBase);
}

void FAbstractAccessibleGenerator::ExportClass(UClass* Class, const FString& SourceHeaderFilename, const FString& GeneratedHeaderFilename, bool bHasChanged)
{
	Log("Class: " + FString(Class->GetPrefixCPP()) + Class->GetName());
	Log("Source Header: " + SourceHeaderFilename);
	Log("");
	FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().ExportClass(Class, SourceHeaderFilename, GeneratedHeaderFilename, bHasChanged);
}

void FAbstractAccessibleGenerator::FinishExport()
{
	FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().FinishExport();

	FString oldWorkingDirectory = FPlatformProcess::GetCurrentWorkingDirectory();
	FString workingDirectory = FAbstractAccessibleGeneratorGlobal::GetConfig().ProjectPath / TEXT("Plugins/Abstract/Source/AbstractAccessibleExtern");
	SetWorkingDirectory(workingDirectory);
	std::system("Build.bat");
	SetWorkingDirectory(oldWorkingDirectory);

}

FString FAbstractAccessibleGenerator::GetGeneratorName() const
{ // this function is for debug info
	return FString("AbsGenerator");
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAbstractAccessibleGenerator, AbstractAccessibleGenerator)
