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

namespace AAGeneratorUtilities
{
    class NodeDefinitionData
    {
    public:
        NodeDefinitionData(
            const FString& name,
            const FString& type,
            const FString& displayText,
            const FString& scriptName,
            const FString& category,
            const FString& keywords,
            const FString& toolTip,
            const FString& returnType,
            const FString& implementationHeader);
        ~NodeDefinitionData() = default;

        void AddInputParam(const FString& name, const FString& type);

        FString WriteOutAADeclaration() const;
        FString WriteOutAAImplementation() const;
        FString WriteOutAADefinitionHeader() const;
        FString WriteOutAADefinitionBody() const;

    private:
        FString m_name;
        FString m_type;
        FString m_displayText;
        FString m_scriptName;
        FString m_category;
        FString m_keywords;
        FString m_toolTip;
        FString m_returnType;
        FString m_implementationHeader;

        TArray<std::pair<FString, FString>> m_inputParams;
    };
}
