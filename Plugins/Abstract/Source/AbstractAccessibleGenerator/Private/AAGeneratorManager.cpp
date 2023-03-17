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

#include "AAGeneratorManager.h"

// #include "UnrealType.h"
// #include "UClassGenerator.h"
// #include "GeneratorDefine.h"
#include "Misc/FileHelper.h"
#include "UObject/UObjectIterator.h"
// #include "ConfigClassGenerator.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"
// #include "ConfigClassDefine.h"
// #include "UStructGenerator.h"
// #include "LuaConfigManager.h"
#include "AbstractAccessibleGeneratorGlobal.h"
// #include "Generator/TArrayGenerator.h"
// #include "Generator/TMapGenerator.h"
// #include "Generator/TSetGenerator.h"
#include "Generators/BaseTypeAAGenerator.h"
#include "Generators/UClassAAGenerator.h"
#include "Generators/AAGeneratorInitUtilities.h"
#include "Interfaces/IPluginManager.h"

void FAAGeneratorManager::Initialize(const FString& RootLocalPath, const FString& RootBuildPath, const FString& OutputDirectory, const FString& IncludeBase)
{
    // DebugProcedure(TEXT("Initialize"));
    m_abstractAccessibleOutDir =
        FPaths::Combine(
            *IPluginManager::Get().FindPlugin("Abstract")->GetBaseDir(),
            TEXT("Source/AbstractAccessibleExtern/Source"));
    m_abstractRuntimeOutDir =
        FPaths::Combine(
            *IPluginManager::Get().FindPlugin("Abstract")->GetBaseDir(),
            TEXT("Source/AbstractAccessibleRuntime/Generated"));
    m_rootLocalPath = RootLocalPath;
    m_rootBuildPath = RootBuildPath;
    m_includeBase = IncludeBase;

    // PropertyTypeAAInternal.Add(TEXT("NOT SUPPORTED\n"));
    // for (const auto& stuff : FAbstractAccessibleGeneratorGlobal::GetConfig().NotSuportClasses)
    // {
    //     PropertyTypeAAInternal.Add(stuff + TEXT("\n"));
    // }
    // PropertyTypeAAInternal.Add(TEXT("DONE\n\n\n"));
}

void FAAGeneratorManager::ExportClass(UClass* Class, const FString& SourceHeaderFilename, const FString& GeneratedHeaderFilename, bool bHasChanged)
{
    // PropertyTypeAAInternal.Add(TEXT("EXPORT BEGIN: ") + Class->GetName() + TEXT("\n"));
    FUClassAAGenerator* generator = new FUClassAAGenerator(Class, SourceHeaderFilename);
    if (AAGeneratorInitUtilities::IsCustomImplementationType(generator->GetClassName()) ||
        AAGeneratorInitUtilities::IsInvalidType(generator->GetClassName()))
    {
        return;
    }

    FUClassAAGenerator::RegisterNew(generator);
    if (generator && CanExportClass(generator) && generator->CanExport())
    {
        generator->ExportToMemory();
        AddGeneratorToMap(generator);
    }
    else if (generator)
    {
        // PropertyTypeAAInternal.Add(pGenerator->GetKey() + TEXT(" EXPORT FAILED!!!\n"));
        // PropertyTypeAAInternal.Add(
        //     (pGenerator == nullptr ? TEXT("True") : TEXT("False")) + FString(TEXT("\n")) +
        //     (CanExportClass(pGenerator) ? TEXT("True") : TEXT("False")) + FString(TEXT("\n")) +
        //     (pGenerator->CanExport() ? TEXT("True") : TEXT("False")) + FString(TEXT("\n")));
        // PropertyTypeAAInternal.Add(SourceHeaderFilename + TEXT("\n\n"));
        delete generator;
    }
    // PropertyTypeAAInternal.Add(TEXT("EXPORT DONE: ") + Class->GetName() + TEXT("\n\n\n\n"));
}

void FAAGeneratorManager::FinishExport()
{
    AAGeneratorInitUtilities::FinalizeValueTypeLoad();

    for (auto& generatorEntry : m_generators)
    {
        generatorEntry.Value->FinalizeMemory();
    }

    SaveToFiles();
    FinishExportPost();
}

bool FAAGeneratorManager::ContainClassName(const FString &ClassName)
{
    return m_generators.Contains(ClassName);
}

IAAGenerator* FAAGeneratorManager::GetGenerator(const FString &ClassName)
{
    IAAGenerator**ppGenerator = m_generators.Find(ClassName);
    return ppGenerator == nullptr ? nullptr : *ppGenerator;
}

bool FAAGeneratorManager::CanExportClass(IAAGenerator*InGenerator) const
{
    return !m_generators.Find(InGenerator->GetKey());
}

void FAAGeneratorManager::AddGeneratorToMap(IAAGenerator *InGenerator)
{
    m_generators.Add(InGenerator->GetKey(), InGenerator);
}

void FAAGeneratorManager::SaveToFiles()
{
    // DebugProcedure(TEXT("SaveToFiles"));

    FString declarationContent =
        TEXT(
"#pragma once\n\n\
#include <AbstractSDK.h>\n\
#include \"ValueTypeDefinitions.h\"\n\
#include \"Core/AABaseTypes.h\"\n\
#include \"Core/AAFVector.h\"\n\
#include \"Core/AAFString.h\"\n\
#include \"Core/AAFName.h\"\n\
#include \"Core/AAFText.h\"\n\
#include \"Core/AAUClass.h\"\n\n");
    for (auto &generatorEntry : m_generators)
    {
        declarationContent += generatorEntry.Value->ExportHeaderContent();
    }

    for (auto &generatorEntry : m_generators)
    {
        declarationContent += generatorEntry.Value->ExportTypeDeclarations();
    }

    declarationContent += FBaseTypeAAGenerator::ExportAllQualifiersAndConversionRules();

    for (auto& generatorEntry : m_generators)
    {
        declarationContent += generatorEntry.Value->ExportConversionRules();
    }

    for (auto &generatorEntry : m_generators)
    {
        for (const auto& nodeDefinitionData : generatorEntry.Value->GetNodeDefinitions())
        {
            declarationContent += nodeDefinitionData.WriteOutAADeclaration();
        }
    }

    FString declarationFilepath = m_abstractAccessibleOutDir / TEXT("UEAllHeader.h");
    if (!FFileHelper::SaveStringToFile(declarationContent, *declarationFilepath))
    {
        // UE_LOG(LogLuaGenerator, Error, TEXT("Failed to save header export:%s"), *GetFileName());
    }

    FString implementationAllIncludeContent = TEXT("namespace AbstractRuntimeGenerated\n{\nvoid InitAll()\n{\n");
    FString implementationAllIncludeHeaderContent = TEXT("#include \"") + declarationFilepath + TEXT("\"\n");
    for (auto& generatorEntry : m_generators)
    {
        implementationAllIncludeHeaderContent += generatorEntry.Value->ExportAdditionalIncludeDirectives();
    }

    for (auto& generatorEntry : m_generators)
    {
        if (!generatorEntry.Value->RequiresImplementation())
        {
            continue;
        }

        FString implementationContent = TEXT("namespace\n{\n");
        for (const auto& nodeDefinitionData : generatorEntry.Value->GetNodeDefinitions())
        {
            implementationContent += nodeDefinitionData.WriteOutAADefinitionHeader();
        }
        implementationContent += TEXT("}\n\n");

        implementationContent += TEXT("namespace AbstractRuntimeGenerated\n{\n");
        implementationContent += TEXT("void InitExterns_") + generatorEntry.Value->GetClassName() + TEXT("()\n{\n");
        for (const auto& nodeDefinitionData : generatorEntry.Value->GetNodeDefinitions())
        {
            implementationContent += nodeDefinitionData.WriteOutAADefinitionBody();
        }
        implementationContent += TEXT("}\n}\n\n");

        FString implementationFilename = (generatorEntry.Value->GetClassName() + TEXT("_absgen.inl"));
        FString implementationFilepath = m_abstractRuntimeOutDir / implementationFilename;
        if (FFileHelper::SaveStringToFile(implementationContent, *implementationFilepath))
        {
            implementationAllIncludeContent += TEXT("InitExterns_") + generatorEntry.Value->GetClassName() + TEXT("();\n");
            implementationAllIncludeHeaderContent += TEXT("#include \"") + implementationFilename + TEXT("\"\n");
        }
        else
        {
            // UE_LOG(LogLuaGenerator, Error, TEXT("Failed to save header export:%s"), *GetFileName());
        }
    }
    implementationAllIncludeContent += TEXT("\n}\n}\n");

    FString implementationAllIncludeFilepath = m_abstractRuntimeOutDir / TEXT("AllInclude.inl");
    if (!FFileHelper::SaveStringToFile(implementationAllIncludeHeaderContent + implementationAllIncludeContent, *implementationAllIncludeFilepath))
    {
        // UE_LOG(LogLuaGenerator, Error, TEXT("Failed to save header export:%s"), *GetFileName());
    }

    FString vcxpropFileContent = {};
    for (auto &generatorEntry : m_generators)
    {
        FString definitionContent = TEXT("#include \"stdafx.h\"\n#include \"UEAllHeader.h\"\n\n");
        for (const auto& nodeDefinitionData : generatorEntry.Value->GetNodeDefinitions())
        {
            definitionContent += nodeDefinitionData.WriteOutAAImplementation();
        }

        FString definitionFilename = TEXT("Generated") / (generatorEntry.Value->GetClassName() + TEXT("_absgen.cpp"));
        FString definitionFilepath = m_abstractAccessibleOutDir / definitionFilename;
        if (FFileHelper::SaveStringToFile(definitionContent, *definitionFilepath))
        {
            vcxpropFileContent += TEXT("<ClCompile Include=\"") + definitionFilename + TEXT("\"/>\n");
        }
        else
        {
            // UE_LOG(LogLuaGenerator, Error, TEXT("Failed to save header export:%s"), *GetFileName());
        }
    }

    vcxpropFileContent =
TEXT("\
<?xml version=\"1.0\" encoding=\"utf-8\"?>\n\
<Project xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">\n\
    <ItemGroup>\n") +
        vcxpropFileContent +
TEXT("\
    </ItemGroup>\n\
</Project>\n");

    FString vcxpropFilepath = m_abstractAccessibleOutDir / TEXT("Generated.props");
    if (!FFileHelper::SaveStringToFile(vcxpropFileContent, *vcxpropFilepath))
    {
        // UE_LOG(LogLuaGenerator, Error, TEXT("Failed to save header export:%s"), *GetFileName());
    }
}

void FAAGeneratorManager::FinishExportPost()
{
    FString PropertyTypes;
    for (const FString& Item : PropertyTypeAAInternal)
    {
        PropertyTypes += Item;
    }

    // PropertyTypes += FString(TEXT("\n"));
    // PropertyTypes.AppendInt(sizeof(FString));
    // PropertyTypes += FString(TEXT("\n"));
    // PropertyTypes.AppendInt(sizeof(FText));
    // PropertyTypes += FString(TEXT("\n"));
    // PropertyTypes.AppendInt(sizeof(FName));
    // PropertyTypes += FString(TEXT("\n"));
    // PropertyTypes.AppendInt(sizeof(FVector));
    // PropertyTypes += FString(TEXT("\n"));

    FFileHelper::SaveStringToFile(PropertyTypes, *(m_abstractAccessibleOutDir / FString("PropertyTypes.txt")));
    FFileHelper::SaveStringToFile(LogContent, *(m_abstractAccessibleOutDir / FString("GeneratorLog.txt")));
    // DebugProcedure(TEXT("FinishExportPost"));
}
