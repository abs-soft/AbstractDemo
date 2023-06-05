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

#pragma once

// #include "GeneratorDefine.h"
// #include "IScriptGenerator.h"
// #include "ConfigClassDefine.h"
// #include "ClassParentsManager.h"
#include "Generators/IAAGenerator.h"

class FAAGeneratorManager
{
public:
    void Initialize(const FString& RootLocalPath, const FString& RootBuildPath, const FString& OutputDirectory, const FString& IncludeBase);
    void ExportClass(UClass* Class, const FString& SourceHeaderFilename, const FString& GeneratedHeaderFilename, bool bHasChanged);
    void FinishExport();

    bool ContainClassName(const FString &ClassName);
    IAAGenerator* GetGenerator(const FString &ClassName);
    void AddGeneratorToMap(IAAGenerator *InGenerator);

    TSet<FString> VariableTypes;
    FString LogContent;
    TArray<FString> PropertyTypeAAInternal;

private:
    bool CanExportClass(IAAGenerator *InGenerator) const;
    void SaveToFiles();
    void FinishExportPost();

    FString m_abstractAccessibleOutDir;
    FString m_abstractRuntimeOutDir;
    FString m_abstractBlueprintFunctionLibrary;
    FString m_rootLocalPath;
    FString m_rootBuildPath;
    FString m_includeBase;
    TMap<FString, IAAGenerator*> m_generators;
    TMap<FString, FProperty*> m_generatorProperties;
};
