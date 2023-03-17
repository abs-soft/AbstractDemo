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

#include "Generators/AAGeneratorUtilities.h"

namespace AAGeneratorUtilities {

NodeDefinitionData::NodeDefinitionData(
    const FString& name,
    const FString& type,
    const FString& displayText,
    const FString& scriptName,
    const FString& category,
    const FString& keywords,
    const FString& toolTip,
    const FString& returnType,
    const FString& implementationHeader)
    : m_name(name)
    , m_type(type)
    , m_displayText(displayText)
    , m_scriptName(scriptName)
    , m_category(category)
    , m_keywords(keywords)
    , m_toolTip(toolTip.Replace(TEXT("\n"), TEXT(" "), ESearchCase::Type::IgnoreCase))
    , m_returnType(returnType)
    , m_implementationHeader(implementationHeader)
    , m_inputParams()
{
    //
}

void NodeDefinitionData::AddInputParam(const FString& name, const FString& type)
{
    m_inputParams.Add({ name, type });
}

FString NodeDefinitionData::WriteOutAADeclaration() const
{
    FString inputParams = {};
    for (const auto& inputParam : m_inputParams)
    {
        inputParams += FString::Printf(TEXT(",\n    ABS_SDK_PARAM(%s, %s)"), *inputParam.second, *inputParam.first);
    }

    return FString::Printf(
        TEXT("ABSTRACT_SDK_NODE_DEFINITION_EXTERN_DECLARE(\n\
    ABS_SDK_PROPERTIES(\n\
        Type=\"%s\",\n\
        NodeDisplayText=\"%s\",\n\
        ScriptName=\"%s\",\n\
        Category=\"%s\",\n\
        Keywords=\"%s\",\n\
        ToolTips=\"%s\"),\n\
    %s,\n\
    %s%s);\n"),
        *m_type,
        *m_displayText,
        *m_scriptName,
        *m_category,
        *m_keywords,
        *m_toolTip,
        *m_name,
        *m_returnType,
        *inputParams);
}

FString NodeDefinitionData::WriteOutAAImplementation() const
{
    FString inputParams = {};
    for (const auto& inputParam : m_inputParams)
    {
        inputParams += FString::Printf(TEXT(",\n    ABS_SDK_PARAM(%s, %s)"), *inputParam.second, *inputParam.first);
    }

    return FString::Printf(
        TEXT("ABSTRACT_SDK_NODE_DEFINITION_EXTERN_IMP(%s, %s%s);\n"),
        *m_name,
        *m_returnType,
        *inputParams);
}

FString NodeDefinitionData::WriteOutAADefinitionHeader() const
{
    FString inputParams = {};
    for (const auto& inputParam : m_inputParams)
    {
        if (inputParams.Len() == 0)
        {
            inputParams += FString::Printf(TEXT("%s %s"), *inputParam.second, *inputParam.first);
        }
        else
        {
            inputParams += FString::Printf(TEXT(", %s %s"), *inputParam.second, *inputParam.first);
        }
    }

    return FString::Printf(
        TEXT("%s %sIMPLEMENTATION(%s)\n{\n%s}\n"),
        *m_returnType,
        *m_name,
        *inputParams,
        *m_implementationHeader);
}

FString NodeDefinitionData::WriteOutAADefinitionBody() const
{
    FString inputParams = {};
    for (const auto& inputParam : m_inputParams)
    {
        inputParams += FString::Printf(TEXT(",\n    ABS_SDK_PARAM(%s, %s)"), *inputParam.second, *inputParam.first);
    }
    return FString::Printf(
        TEXT("ABSTRACT_SDK_NODE_DEFINITION_EXTERN_DEFINE(\n    %s,\n    %sIMPLEMENTATION,\n    %s%s);\n"),
        *m_name,
        *m_name,
        *m_returnType,
        *inputParams);
}

}
