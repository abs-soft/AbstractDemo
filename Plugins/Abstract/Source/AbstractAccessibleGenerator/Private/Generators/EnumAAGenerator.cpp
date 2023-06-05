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

#include "Generators/EnumAAGenerator.h"

// #include "UnrealType.h"
#include "Templates/Casts.h"
#include "Misc/FileHelper.h"
// #include "UObjectIterator.h"
// #include "ScriptGeneratorManager.h"

#include "AbstractAccessibleGeneratorGlobal.h"
#include <algorithm>


// #include "UStructGenerator.h"
// #include "UnrealType.h"
// #include "Templates/Casts.h"
// #include "Misc/FileHelper.h"
// #include "UObjectIterator.h"

FString FEnumAAGenerator::GetExportableName(UEnum* enumData)
{
	return TEXT("AA") + enumData->CppType.Replace(TEXT("::"), TEXT(""));
}

FEnumAAGenerator::FEnumAAGenerator(UEnum* enumData)
	: m_enumData(enumData)
{
	//
}

FEnumAAGenerator::~FEnumAAGenerator()
{

}

FString FEnumAAGenerator::GetKey() const
{
	return GetClassName();
}

bool FEnumAAGenerator::CanExport() const
{
	return m_enumData != nullptr;
}

void FEnumAAGenerator::ExportToMemory()
{
	//
}

void FEnumAAGenerator::FinalizeMemory()
{
	//
}

FString FEnumAAGenerator::GetClassName() const
{
    return m_enumData->CppType.Replace(TEXT("::"), TEXT("_"));
}

FString FEnumAAGenerator::ExportName() const
{
	return GetExportableName(m_enumData);
}

FString FEnumAAGenerator::ExportHeaderContent() const
{
	return {};
}

FString FEnumAAGenerator::ExportConversionRules() const
{
	return {};
}

FString FEnumAAGenerator::ExportTypeDeclarations() const
{
	FString prefix = m_enumData->GenerateEnumPrefix();
	FString result =
		FString::Printf(
			TEXT("ABSTRACT_SDK_ENUM(ABS_SDK_PROPERTIES(DisplayText = \"%s\", ScriptName = \"%s\"), %s)\n"),
			*m_enumData->GetDisplayNameText().ToString(),
			*m_enumData->GetName(),
			*ExportName());
	for (int enumIndex = 0; enumIndex < m_enumData->NumEnums(); ++enumIndex)
	{
        result +=
        	TEXT("\tABSTRACT_SDK_ENUM_ENTRY(") +
        	m_enumData->GetDisplayNameTextByIndex(enumIndex).ToString() +
        	TEXT(", ") +
			FString::Printf(TEXT("%lld"), m_enumData->GetValueByIndex(enumIndex)) +
        	TEXT(")\n");
	}
	result += TEXT("ABSTRACT_SDK_ENUM_END()\n");
	return result;
}

bool FEnumAAGenerator::RequiresImplementation() const
{
	return false;
}

FString FEnumAAGenerator::ExportAdditionalIncludeDirectives() const
{
	return {};
}

FString FEnumAAGenerator::ExportBlueprintFunctionLibraryForwardDecl() const
{
	return {};
}

FString FEnumAAGenerator::ExportBlueprintFunctionLibraryDeclarations() const
{
	return {};
}

FString FEnumAAGenerator::ExportBlueprintFunctionLibraryDefinitions() const
{
	return {};
}
