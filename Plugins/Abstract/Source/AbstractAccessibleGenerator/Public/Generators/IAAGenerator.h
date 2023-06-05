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

#include "AAGeneratorUtilities.h"

class IAAGenerator
{
public:
    enum class Type
    {
        Invalid,
        BaseType,
        UClass,
        UStruct,
        Array
    };

    virtual ~IAAGenerator() = default;

    virtual bool CanExport() const = 0;
    virtual void ExportToMemory() = 0;
    virtual void FinalizeMemory() = 0;
    virtual FString GetKey() const = 0;
    virtual FString GetClassName() const = 0;

    virtual FString ExportName() const = 0;
    virtual FString ExportHeaderContent() const = 0;
    virtual FString ExportConversionRules() const = 0;
    virtual FString ExportTypeDeclarations() const = 0;
    virtual bool RequiresImplementation() const = 0;
    virtual FString ExportAdditionalIncludeDirectives() const = 0;

    virtual FString ExportBlueprintFunctionLibraryForwardDecl() const = 0;
    virtual FString ExportBlueprintFunctionLibraryDeclarations() const = 0;
    virtual FString ExportBlueprintFunctionLibraryDefinitions() const = 0;

    virtual Type GetType() const { return Type::Invalid; };

    void AddNodeDefinition(const AAGeneratorUtilities::NodeDefinitionData& newEntry);
    const TArray<AAGeneratorUtilities::NodeDefinitionData>& GetNodeDefinitions() const;

private:
    TArray<AAGeneratorUtilities::NodeDefinitionData> m_nodeDefinitions;
};
