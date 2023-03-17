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

#include "IAAGenerator.h"

namespace AAGeneratorInitUtilities
{
    void DebugPrintProp(FProperty* property);
    class ValueTypeBase;
    void InitValueTypeGenerator();
    ValueTypeBase& ResolveValueType(FProperty* property);
    bool IsCustomImplementationType(FString name);
    bool IsInvalidType(FString name);
    void FinalizeValueTypeLoad();

    bool CanExportProperty(FProperty* property);
    bool CanExportFunction(UFunction* function);
    FString GetPropertyType(FProperty* property, FString& pureTypeOut);

    class ValueTypeTreeTraversalContext;
    class ValueTypeBase
    {
    public:
        enum class ClassType
        {
            InvalidValueType,
            PureValueType,
            EnumValueType,
            ValueTypeQualifier,
            ClassValueType
        };
        virtual ClassType GetClassType() const = 0;
        virtual ~ValueTypeBase() {}

        virtual FString GetDisplayName() const = 0;
        virtual bool Supported(ValueTypeTreeTraversalContext& context) const = 0;
        virtual FString GetSourceType(ValueTypeTreeTraversalContext& context) const = 0;
        virtual FString GetExportName(ValueTypeTreeTraversalContext& context) const = 0;
        virtual FString ConvertToSourceType(ValueTypeTreeTraversalContext& context, const FString& value) const = 0;
        virtual FString ConvertToAAType(ValueTypeTreeTraversalContext& context, const FString& value) const = 0;
        virtual FString GetDebugInfo() const = 0;
    };

    class InvalidValueType : public ValueTypeBase
    {
    public:
        virtual ClassType GetClassType() const { return ClassType::InvalidValueType; }

        InvalidValueType(const FString& type);
        virtual ~InvalidValueType() override {}

        virtual FString GetDisplayName() const override;
        virtual bool Supported(ValueTypeTreeTraversalContext& context) const override;
        virtual FString GetSourceType(ValueTypeTreeTraversalContext& context) const override;
        virtual FString GetExportName(ValueTypeTreeTraversalContext& context) const override;
        virtual FString ConvertToSourceType(ValueTypeTreeTraversalContext& context, const FString& value) const override;
        virtual FString ConvertToAAType(ValueTypeTreeTraversalContext& context, const FString& value) const override;
        virtual FString GetDebugInfo() const override;

    private:
        FString m_invalidType;
    };

    class PureValueType : public ValueTypeBase
    {
    public:
        virtual ClassType GetClassType() const { return ClassType::PureValueType; }

        enum class Type
        {
            BaseType,
            Class,
            Struct
        };

        PureValueType(Type type, const FString& name);
        virtual ~PureValueType() override {}

        Type GetType() const;
        const FString& GetName() const;

        virtual FString GetDisplayName() const override;
        virtual bool Supported(ValueTypeTreeTraversalContext& context) const override;
        virtual FString GetSourceType(ValueTypeTreeTraversalContext& context) const override;
        virtual FString GetExportName(ValueTypeTreeTraversalContext& context) const override;
        virtual FString ConvertToSourceType(ValueTypeTreeTraversalContext& context, const FString& value) const override;
        virtual FString ConvertToAAType(ValueTypeTreeTraversalContext& context, const FString& value) const override;
        virtual FString GetDebugInfo() const override;

    private:
        Type m_type;
        FString m_name;
    };

    class EnumValueType : public ValueTypeBase
    {
    public:
        virtual ClassType GetClassType() const override { return ClassType::EnumValueType; }

        EnumValueType(UEnum* enumData);
        virtual ~EnumValueType() override {}

        UEnum* GetEnumData() const;

        virtual FString GetDisplayName() const override;
        virtual bool Supported(ValueTypeTreeTraversalContext& context) const override;
        virtual FString GetSourceType(ValueTypeTreeTraversalContext& context) const override;
        virtual FString GetExportName(ValueTypeTreeTraversalContext& context) const override;
        virtual FString ConvertToSourceType(ValueTypeTreeTraversalContext& context, const FString& value) const override;
        virtual FString ConvertToAAType(ValueTypeTreeTraversalContext& context, const FString& value) const override;
        virtual FString GetDebugInfo() const override;

    private:
        UEnum* m_enumData;
    };

    class ValueTypeQualifier : public ValueTypeBase
    {
    public:
        virtual ClassType GetClassType() const { return ClassType::ValueTypeQualifier; }

        enum class Type
        {
            Const,
            Out,
            Reference,
            SubClass,
            ObjectPtr,
            WeakObject,
            Array,
        };

        ValueTypeQualifier(Type type);
        virtual ~ValueTypeQualifier() override {}

        void AddChild(ValueTypeBase& child);

        const TArray<ValueTypeBase*>& GetChildren() const;
        Type GetType() const;

        virtual FString GetDisplayName() const override;
        virtual bool Supported(ValueTypeTreeTraversalContext& context) const override;
        virtual FString GetSourceType(ValueTypeTreeTraversalContext& context) const override;
        virtual FString GetExportName(ValueTypeTreeTraversalContext& context) const override;
        virtual FString ConvertToSourceType(ValueTypeTreeTraversalContext& context, const FString& value) const override;
        virtual FString ConvertToAAType(ValueTypeTreeTraversalContext& context, const FString& value) const override;
        virtual FString GetDebugInfo() const override;

    private:
        Type m_type;
        TArray<ValueTypeBase*> m_childrenTypes;
    };

    class UClassValueType : public ValueTypeBase
    {
    public:
        virtual ClassType GetClassType() const override { return ClassType::ClassValueType; }

        UClassValueType(ValueTypeBase* childType);
        virtual ~UClassValueType() override {}

        virtual FString GetDisplayName() const override;
        virtual bool Supported(ValueTypeTreeTraversalContext& context) const override;
        virtual FString GetSourceType(ValueTypeTreeTraversalContext& context) const override;
        virtual FString GetExportName(ValueTypeTreeTraversalContext& context) const override;
        virtual FString ConvertToSourceType(ValueTypeTreeTraversalContext& context, const FString& value) const override;
        virtual FString ConvertToAAType(ValueTypeTreeTraversalContext& context, const FString& value) const override;
        virtual FString GetDebugInfo() const override;

    private:
        ValueTypeBase* m_childType;
    };

    enum class ValueTypeTreeTraversalType
    {
        Default,
        Return,
        InputParam,
        TemplateParam,
        ConversionTemplateParam,
        GetReturnType,
        SetInputType
    };

    class ValueTypeTreeTraversalContext
    {
    public:
        ValueTypeTreeTraversalContext(ValueTypeTreeTraversalType type);

        ValueTypeTreeTraversalType GetType();
        FString GetExportPrefix();

        void PushQualifier(ValueTypeQualifier::Type type);
        bool HasQualifier(ValueTypeQualifier::Type type);

    private:
        ValueTypeTreeTraversalType m_type;
        TArray<ValueTypeQualifier::Type> m_qualifiers;
    };

    ///////////////////////////////////////////////////////////////////////////////////
    // Data Member
    class DataMemberExportInfo
    {
    public:
        static DataMemberExportInfo Construct(FProperty *property);

        bool Supported(ValueTypeTreeTraversalType type) const;
        const ValueTypeBase& GetType() const;
        const FString& GetName() const;
        bool SupportsGet() const;
        bool SupportsSet() const;
        bool HasDisplayName() const;
        const FText& GetDisplayName() const;
        FString GetTypeExport(ValueTypeTreeTraversalType type) const;
        FString ConvertToSourceType(ValueTypeTreeTraversalType type, const FString& value) const;
        FString ConvertToAAType(ValueTypeTreeTraversalType type, const FString& value) const;

        FString GetDebugInfo() const;

    private:
        DataMemberExportInfo();
        DataMemberExportInfo(const ValueTypeBase& type, const FString& name, const FText& displayName, bool supportsSet);

        const ValueTypeBase* m_type;
        FString m_name;
        FText m_displayName;
        bool m_supportsSet;
    };

    ///////////////////////////////////////////////////////////////////////////////////
    // Function Member
    struct FunctionMemberExportInfo
    {
    public:
        static FunctionMemberExportInfo Construct(UClass* uclass, UFunction* function);
        static FunctionMemberExportInfo Construct(UStruct* ustruct, UFunction* function);

        bool Supported() const;
        const FString& GetName() const;
        const FString& GetCategories() const;
        const FString& GetToolTips() const;
        const FString& GetKeywords() const;
        bool IsStatic() const;
        bool IsVoidReturn() const;
        bool HasSuper() const;
        const FString& GetSuperName() const;
        const DataMemberExportInfo& GetReturnParam() const;
        const TArray<DataMemberExportInfo>& GetInputParams() const;
        bool HasDisplayName() const;
        const FText& GetDisplayName() const;

        FString GetDebugInfo() const;

    private:
        FunctionMemberExportInfo(const FString& name);
        FunctionMemberExportInfo(UFunction* function);

        void SetSuperClassName(const FString& superClassName);

        FString m_name;
        FText m_displayName;
        FString m_categories;
        FString m_toolTips;
        FString m_keywords;
        bool m_static;
        bool m_voidReturn;
        FString m_superClassName;
        DataMemberExportInfo m_returnType;
        TArray<DataMemberExportInfo> m_inputParams;
    };

    ///////////////////////////////////////////////////////////////////////////////////
    // Export Info
    class ClassExportInfo
    {
    public:
        void Init(const FString& className);
        void AddDataMember(const DataMemberExportInfo& dataMemberInfo);
        void AddFunctionMember(const FunctionMemberExportInfo& funcMemberInfo);

        const TMap<FString, FunctionMemberExportInfo>& GetFunctionMembers() const;
        const TMap<FString, DataMemberExportInfo>& GetDataMembers() const;

    private:
        FString m_className;
        TMap<FString, FunctionMemberExportInfo> m_functionMembers;
        TMap<FString, DataMemberExportInfo> m_dataMembers;
    };
}
