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

#include "Generators/BaseTypeAAGenerator.h"

// #include "UnrealType.h"
#include "Templates/Casts.h"
#include "Misc/FileHelper.h"
// #include "UObjectIterator.h"
// #include "ScriptGeneratorManager.h"

#include "AbstractAccessibleGeneratorGlobal.h"

#include <algorithm>
#include <array>

namespace
{
	enum class SupportedBaseTypes
	{
		Uint8,
		Uint16,
		Uint32,
		Uint64,
		Int8,
		Int16,
		Int32,
		Int64,
		Float,
		Double,
		Bool,

		Count
	};
	constexpr std::size_t TypeCount = static_cast<std::size_t>(SupportedBaseTypes::Count);

	const std::array<FString, TypeCount> SupportedBaseTypeNames =
	{
		FString("uint8"),
		FString("uint16"),
		FString("uint32"),
		FString("uint64"),
		FString("int8"),
		FString("int16"),
		FString("int32"),
		FString("int64"),
		FString("float"),
		FString("double"),
		FString("bool"),
	};

	const std::array<FString, TypeCount> NativeBaseTypes =
	{
		FString("uint8_t"),
		FString("uint16_t"),
		FString("uint32_t"),
		FString("uint64_t"),
		FString("int8_t"),
		FString("int16_t"),
		FString("int32_t"),
		FString("int64_t"),
		FString("float"),
		FString("double"),
		FString("bool"),
	};

	const std::array<FString, TypeCount> ExportedNames =
	{
		FString("AABuInt8"),
		FString("AABuInt16"),
		FString("AABuInt32"),
		FString("AABuInt64"),
		FString("AABInt8"),
		FString("AABInt16"),
		FString("AABInt32"),
		FString("AABInt64"),
		FString("AABFloat"),
		FString("AABDouble"),
		FString("AABBool"),
	};
}

bool FBaseTypeAAGenerator::Supported(const FString& name)
{
	return std::any_of(
		SupportedBaseTypeNames.begin(),
		SupportedBaseTypeNames.end(),
		[&](const FString& typeName) { return name.Compare(typeName) == 0; });
}

void FBaseTypeAAGenerator::ConstructAllGenerators()
{
	for (int index = 0; index < TypeCount; ++index)
	{
        auto* generator = new FBaseTypeAAGenerator(index);
        generator->ExportToMemory();
        FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().AddGeneratorToMap(generator);
	}
}

FString FBaseTypeAAGenerator::GetExportName(const FString& name)
{
	int index = 0;
	for (; index < TypeCount; ++index)
	{
		if (name.Compare(SupportedBaseTypeNames.at(index)) == 0)
		{
			break;
		}
	}

	return ExportedNames.at(index);
}

FString FBaseTypeAAGenerator::ExportAllQualifiersAndConversionRules()
{
	return {};
}

FBaseTypeAAGenerator::FBaseTypeAAGenerator(long index) : m_index(index)
{
	//
}

FBaseTypeAAGenerator::~FBaseTypeAAGenerator()
{
	//
}

FString FBaseTypeAAGenerator::GetKey() const
{
	return SupportedBaseTypeNames.at(m_index);
}

bool FBaseTypeAAGenerator::CanExport()const 
{
	return true;
}

void FBaseTypeAAGenerator::ExportToMemory()
{
	//
}

void FBaseTypeAAGenerator::FinalizeMemory()
{
	//
}

FString FBaseTypeAAGenerator::GetClassName() const
{
	return SupportedBaseTypeNames.at(m_index);
}

FString FBaseTypeAAGenerator::ExportName() const
{
	return ExportedNames.at(m_index);
}

FString FBaseTypeAAGenerator::ExportHeaderContent() const
{
	return {};
}

FString FBaseTypeAAGenerator::ExportConversionRules() const
{
	return {};
}

FString FBaseTypeAAGenerator::ExportTypeDeclarations() const
{
	return {};
}

bool FBaseTypeAAGenerator::RequiresImplementation() const
{
	return false;
}

FString FBaseTypeAAGenerator::ExportAdditionalIncludeDirectives() const
{
	return {};
}

FString FBaseTypeAAGenerator::ExportBlueprintFunctionLibraryForwardDecl() const
{
	return {};
}

FString FBaseTypeAAGenerator::ExportBlueprintFunctionLibraryDeclarations() const
{
	return {};
}

FString FBaseTypeAAGenerator::ExportBlueprintFunctionLibraryDefinitions() const
{
	return {};
}
