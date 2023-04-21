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

#include "Generators/TArrayAAGenerator.h"
#include "Generators/AAGeneratorInitUtilities.h"

TArrayAAGenerator::TArrayAAGenerator(const AAGeneratorInitUtilities::ValueTypeQualifier* qualifier)
    : m_qualifier(qualifier)
{
    //
}

TArrayAAGenerator::~TArrayAAGenerator()
{
    //
}

FString TArrayAAGenerator::GetKey() const
{
    return ExportName();
}

bool TArrayAAGenerator::CanExport() const
{
    AAGeneratorInitUtilities::ValueTypeTreeTraversalContext context(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Default);
    return m_qualifier->Supported(context);
}

void TArrayAAGenerator::ExportToMemory()
{
    //
}

void TArrayAAGenerator::FinalizeMemory()
{
    AAGeneratorInitUtilities::ValueTypeTreeTraversalContext context0(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Default);
    AAGeneratorInitUtilities::ValueTypeTreeTraversalContext context1(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Default);
    AAGeneratorInitUtilities::ValueTypeTreeTraversalContext context2(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Default);
    AAGeneratorInitUtilities::ValueTypeTreeTraversalContext context3(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Default);
    constexpr auto resetContexts = [&]() {
        context0 = AAGeneratorInitUtilities::ValueTypeTreeTraversalContext(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Default);
        context1 = AAGeneratorInitUtilities::ValueTypeTreeTraversalContext(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Default);
        context2 = AAGeneratorInitUtilities::ValueTypeTreeTraversalContext(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Default);
        context3 = AAGeneratorInitUtilities::ValueTypeTreeTraversalContext(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Default);
    };

    AAGeneratorUtilities::NodeDefinitionData makeNodeDefinition(
        FString::Printf(TEXT("Make%s"), *ExportName()),
        TEXT("Evaluation"),
        FString::Printf(TEXT("Make New Array of %s"), *m_qualifier->GetChildren()[0]->GetDisplayName()),
        FString::Printf(TEXT("MakeNewArrayOf%s"), *m_qualifier->GetChildren()[0]->GetDisplayName()),
        TEXT("Array"),
        TEXT(""),
        FString::Printf(TEXT("Makes a new array of %s"), *m_qualifier->GetChildren()[0]->GetDisplayName()),
        *ExportName(),
        *FString::Printf(
            TEXT("%s result = {};\nnew (&result) %s();\nreturn result;\n"),
            *ExportName(),
            *m_qualifier->GetSourceType(context0)));

    resetContexts();

    AAGeneratorUtilities::NodeDefinitionData addElementNodeDefinition(
        TEXT("AddArrayElement"),
        TEXT("Execution"),
        TEXT("Add Array Element"),
        TEXT("Add"),
        FString::Printf(TEXT("%sArray"), *m_qualifier->GetChildren()[0]->GetDisplayName()),
        FString::Printf(TEXT("array append push %s"), *m_qualifier->GetChildren()[0]->GetDisplayName().ToLower()),
        FString::Printf(TEXT("Adds a new element to an array of %s"), *m_qualifier->GetChildren()[0]->GetDisplayName()),
        TEXT("Execution"),
        *FString::Printf(
            TEXT("%s.Add(%s);\n"),
            *m_qualifier->ConvertToSourceType(context0, TEXT("Target")),
            *m_qualifier->GetChildren()[0]->ConvertToSourceType(context1, TEXT("NewElement"))));
    addElementNodeDefinition.AddInputParam(TEXT("Target"), FString::Printf(TEXT("__INREF__%s"), *ExportName()));
    addElementNodeDefinition.AddInputParam(TEXT("NewElement"), FString::Printf(TEXT("%s"), *m_qualifier->GetChildren()[0]->GetExportName(context2)));

    resetContexts();

    AAGeneratorUtilities::NodeDefinitionData getLengthNodeDefinition(
        TEXT("GetArrayLength"),
        TEXT("Evaluation"),
        TEXT("Get Array Length"),
        TEXT("Length"),
        FString::Printf(TEXT("%sArray"), *m_qualifier->GetChildren()[0]->GetDisplayName()),
        FString::Printf(TEXT("array length %s"), *m_qualifier->GetChildren()[0]->GetDisplayName().ToLower()),
        FString::Printf(TEXT("Get the length of an array of %s"), *m_qualifier->GetChildren()[0]->GetDisplayName()),
        TEXT("AABInt32"),
        *FString::Printf(
            TEXT("return %s.Num();\n"),
            *m_qualifier->ConvertToSourceType(context0, TEXT("Target"))));
    getLengthNodeDefinition.AddInputParam(TEXT("Target"), FString::Printf(TEXT("__INREF__%s"), *ExportName()));

    resetContexts();

    AAGeneratorUtilities::NodeDefinitionData removeAtNodeDefinition(
        TEXT("RemoveArrayElementAt"),
        TEXT("Execution"),
        TEXT("Remove Array Element At"),
        TEXT("RemoveAt"),
        FString::Printf(TEXT("%sArray"), *m_qualifier->GetChildren()[0]->GetDisplayName()),
        FString::Printf(TEXT("array remove %s"), *m_qualifier->GetChildren()[0]->GetDisplayName().ToLower()),
        FString::Printf(TEXT("Removes an element of an array of %s at the specified index"), *m_qualifier->GetChildren()[0]->GetDisplayName()),
        TEXT("Execution"),
        *FString::Printf(
            TEXT("%s.RemoveAt(%s);\n"),
            *m_qualifier->ConvertToSourceType(context0, TEXT("Target")),
            TEXT("Index")));
    removeAtNodeDefinition.AddInputParam(TEXT("Target"), FString::Printf(TEXT("__INREF__%s"), *ExportName()));
    removeAtNodeDefinition.AddInputParam(TEXT("Index"), TEXT("AABInt32"));

    resetContexts();

    AAGeneratorInitUtilities::ValueTypeTreeTraversalContext returnContext(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Return);
    const bool isEnumArray = m_qualifier->GetChildren()[0]->GetClassType() == AAGeneratorInitUtilities::ValueTypeBase::ClassType::EnumValueType;
    if (!isEnumArray)
    {
        returnContext.PushQualifier(AAGeneratorInitUtilities::ValueTypeQualifier::Type::Reference);
    }
    AAGeneratorUtilities::NodeDefinitionData getAtNodeDefinition(
        TEXT("GetArrayElementAt"),
        TEXT("Evaluation"),
        TEXT("Get Array Element At"),
        TEXT("ElementAt"),
        FString::Printf(TEXT("%sArray"), *m_qualifier->GetChildren()[0]->GetDisplayName()),
        FString::Printf(TEXT("array get %s"), *m_qualifier->GetChildren()[0]->GetDisplayName().ToLower()),
        FString::Printf(TEXT("Gets an element of an array of %s at the specified index"), *m_qualifier->GetChildren()[0]->GetDisplayName()),
        isEnumArray ?
            *m_qualifier->GetChildren()[0]->GetExportName(context0) :
            FString::Printf(TEXT("__REF__%s"), *m_qualifier->GetChildren()[0]->GetExportName(context0)),
        *FString::Printf(
            TEXT("return %s;\n"),
            *m_qualifier->GetChildren()[0]->ConvertToAAType(
                returnContext,
                FString::Printf(
                    TEXT("%s[Index]"),
                    *m_qualifier->ConvertToSourceType(context1, TEXT("Target"))))));
    getAtNodeDefinition.AddInputParam(TEXT("Target"), FString::Printf(TEXT("__INREF__%s"), *ExportName()));
    getAtNodeDefinition.AddInputParam(TEXT("Index"), TEXT("AABInt32"));

    AddNodeDefinition(makeNodeDefinition);
    AddNodeDefinition(addElementNodeDefinition);
    AddNodeDefinition(getLengthNodeDefinition);
    AddNodeDefinition(removeAtNodeDefinition);
    AddNodeDefinition(getAtNodeDefinition);
}

FString TArrayAAGenerator::GetClassName() const
{
    AAGeneratorInitUtilities::ValueTypeTreeTraversalContext context(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Default);
    return m_qualifier->GetExportName(context);
}

FString TArrayAAGenerator::ExportName() const
{
    return GetClassName();
}

FString TArrayAAGenerator::ExportHeaderContent() const
{
    return {};
}

FString TArrayAAGenerator::ExportConversionRules() const
{
    return {};
}

FString TArrayAAGenerator::ExportTypeDeclarations() const
{
    return FString::Printf(
        TEXT("ABSTRACT_SDK_VALUE_TYPE_DEFINITION_SIZED_EXTERN(ABS_SDK_PROPERTIES(DisplayText = \"%s\", ScriptName = \"%s\"), %s, 16);\n"),
        *FString::Printf(TEXT("Array of %s"), *m_qualifier->GetChildren()[0]->GetDisplayName()),
        *FString::Printf(TEXT("ArrayOf%s"), *m_qualifier->GetChildren()[0]->GetDisplayName()),
        *ExportName());
}

bool TArrayAAGenerator::RequiresImplementation() const
{
    return true;
}

FString TArrayAAGenerator::ExportAdditionalIncludeDirectives() const
{
    return {};
}
