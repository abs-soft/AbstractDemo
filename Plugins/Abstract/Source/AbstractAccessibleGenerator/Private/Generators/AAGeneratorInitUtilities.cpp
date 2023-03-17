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

#include "Generators/AAGeneratorInitUtilities.h"
#include "Generators/UStructAAGenerator.h"
#include "Generators/BaseTypeAAGenerator.h"
#include "Generators/EnumAAGenerator.h"
#include "Generators/TArrayAAGenerator.h"

#include "AbstractAccessibleGeneratorGlobal.h"
#include "CoreUObject.h"

#include <algorithm>
#include <thread>

namespace
{
    TMap<FString, AAGeneratorInitUtilities::ValueTypeBase*> valueTypeRegistry = {};
    TSet<FString> invalidTypes = {};
    const TSet<FString> forceInvalidTypes =
    {
        "UAsyncActionLoadPrimaryAsset",
        "UAsyncActionLoadPrimaryAssetClass",
        "UAsyncActionLoadPrimaryAssetList",
        "UAsyncActionLoadPrimaryAssetClassList",
        "UAsyncActionChangePrimaryAssetBundles",
        "FScriptTypedElementHandle",
        "FAudioParameter",
        "FScriptTypedElementListProxy",
        "FMatrix",
        "FBox2D",
        "FTransform",
        "FRandomStream",
        "FSoftObjectPath",
        "FSoftClassPath",
        "FPrimaryAssetType",
        "FPolyglotTextData",
        "FChaosSolverConfiguration",
        "FAnimatedBoneAttribute",
        "FMontageBlendSettings",
        "FBlendProfileBoneEntry",
        "FPerBoneInterpolation",
        "FRuntimeFloatCurve",
        "FPrimaryAssetRulesOverride",
        "FPrimaryAssetRulesCustomOverride",
        "FSkeletalMeshLODGroupSettings",
        "FSkeletalMaterial",
        "FStaticMaterial",
        "FSpatialHashStreamingGrid",
        "FStaticMeshSourceModel",
        "FStaticMeshComponentLODInfo",
        "FLevelCollection",
        "FHLODProxyMesh",
        "FSmartNameContainer",
        "FReplicatedStaticActorDestructionInfo",
        "FSoundClassProperties",
        "FNavGraphNode",
        "FGameplayTagContainer",
        "FGameplayTagQuery",
        "FFloatDistribution",
        "FAudioEQEffect",
        "FISMComponentData",
        "FCharacterMovementComponentPostPhysicsTickFunction",
        "FGPUSpriteEmitterInfo",
        "FMovieSceneFloatChannel",
        "FMovieSceneRootEvaluationTemplateInstance",
        // Due to name collision
        "UBlackboardKeyType_Int",
        "UBlackboardKeyType_Bool",
        "UBlackboardKeyType_Float",
        "UBlackboardKeyType_String",
        "UBlackboardKeyType_Name",
        "UBlackboardKeyType_Object",
        "UBlackboardKeyType_Class",
        "UBlackboardKeyType_Vector",
        "UBlackboardKeyType_Rotator",
        "UClass",
        "FVector2MaterialInput",
        "FLevelSimplificationDetails",
        "UMaterialInterfaceEditorOnlyData",
        "UMaterialFunctionInterfaceEditorOnlyData",
        "UContentBundleDuplicateForPIEHelper",
        "UContentBundleUnsavedActorMonitor",
        "UTransactionDiffingTestObject",
        "URuntimeSpatialHashExternalStreamingObject",
        "UMaterialExpressionDistanceFieldApproxAO",
        "UMaterialExpressionIsOrthographic",
        "UMaterialExpressionNaniteReplace",
        "UMaterialExpressionVolumetricCloudEmptySpaceSkippingInput",
        "FActorTickFunction",
        "FActorComponentTickFunction",
        "FGeometry"
    };
    const TSet<FString> customImplementationTypes =
    {
        "FString",
        "FName",
        "FText",
        "FVector"
    };

    AAGeneratorInitUtilities::ValueTypeBase& ResolveValueTypeFromUClass(UClass* uclass)
    {
        if (uclass)
        {
            FString className = uclass->GetPrefixCPP() + uclass->GetName();
            className.RemoveSpacesInline();
            AAGeneratorInitUtilities::ValueTypeBase* searchResult = valueTypeRegistry.FindRef(className);
            if (searchResult)
            {
                return *searchResult;
            }

            auto* result = new AAGeneratorInitUtilities::PureValueType(AAGeneratorInitUtilities::PureValueType::Type::Class, className);
            return *result;
        }

        auto* invalidResult = new AAGeneratorInitUtilities::InvalidValueType(TEXT("NULL"));
        valueTypeRegistry.Add(TEXT("6044F51543D04EFDA7C0D6023A7A52A9"), invalidResult);
        return *invalidResult;
    }

    template<typename Callback>
    bool ForEachValueType(
        AAGeneratorInitUtilities::ValueTypeBase* root,
        AAGeneratorInitUtilities::ValueTypeBase::ClassType targetType,
        Callback callback)
    {
        if (root->GetClassType() == targetType)
        {
            if (callback(root))
            {
                return true;
            }
        }

        if (root->GetClassType() == AAGeneratorInitUtilities::ValueTypeBase::ClassType::ValueTypeQualifier)
        {
            for (auto* child : reinterpret_cast<AAGeneratorInitUtilities::ValueTypeQualifier*>(root)->GetChildren())
            {
                if (ForEachValueType(child, targetType, callback))
                {
                    return true;
                }
            }
        }

        return false;
    }
}

namespace AAGeneratorInitUtilities
{

void DebugPrintProp(FProperty* property)
{
    if (property == nullptr)
    {
        return;
    }

    FString dummy;
    FString debugPrint = property->GetName() + TEXT("[") + AAGeneratorInitUtilities::GetPropertyType(property, dummy) + TEXT("]");
    // 
    // if (property->IsA(FEnumProperty::StaticClass()))
    // {
    //     auto* enumProp = CastField<FEnumProperty>(property);
    //     debugPrint += enumProp->GetEnum()->CppType;
    // 
    //     switch (enumProp->GetEnum()->GetCppForm())
    //     {
    //     case UEnum::ECppForm::Regular:
    //     {
    //         debugPrint += TEXT("[R]");
    //     }
    //     break;
    // 
    //     case UEnum::ECppForm::Namespaced:
    //     {
    //         debugPrint += TEXT("[NS]");
    //     }
    //     break;
    // 
    //     case UEnum::ECppForm::EnumClass:
    //     {
    //         debugPrint += TEXT("[EC]");
    //     }
    //     break;
    //     }
    // }
    // else if (property->IsA(FNumericProperty::StaticClass()))
    // {
    //     auto* numProperty = CastField<FNumericProperty>(property);
    //     UEnum* propertyEnum = numProperty->GetIntPropertyEnum();
    //     if (propertyEnum == nullptr)
    //     {
    //         return;
    //     }
    //     else
    //     {
    //         debugPrint += propertyEnum->CppType;
    //         switch (propertyEnum->GetCppForm())
    //         {
    //         case UEnum::ECppForm::Regular:
    //         {
    //             debugPrint += TEXT("[R]");
    //         }
    //         break;
    // 
    //         case UEnum::ECppForm::Namespaced:
    //         {
    //             debugPrint += TEXT("[NS]");
    //         }
    //         break;
    // 
    //         case UEnum::ECppForm::EnumClass:
    //         {
    //             debugPrint += TEXT("[EC]");
    //         }
    //         break;
    //         }
    //     }
    // }
    // else
    // {
    //     return;
    // }

    if (property->HasAnyPropertyFlags(CPF_BlueprintVisible))
    {
        debugPrint += TEXT("|BlueprintVisible");
    }
    if (property->HasAnyPropertyFlags(CPF_BlueprintReadOnly))
    {
        debugPrint += TEXT("|BlueprintReadOnly");
    }
    if (property->HasAnyPropertyFlags(CPF_EditFixedSize))
    {
        debugPrint += TEXT("|EditFixedSize");
    }
    if (property->HasAnyPropertyFlags(CPF_ConstParm))
    {
        debugPrint += TEXT("|ConstParm");
    }
    if (property->HasAnyPropertyFlags(CPF_Parm))
    {
        debugPrint += TEXT("|Parm");
    }
    if (property->HasAnyPropertyFlags(CPF_OutParm))
    {
        debugPrint += TEXT("|OutParm");
    }
    if (property->HasAnyPropertyFlags(CPF_ReturnParm))
    {
        debugPrint += TEXT("|ReturnParm");
    }
    if (property->HasAnyPropertyFlags(CPF_ReferenceParm))
    {
        debugPrint += TEXT("|ReferenceParm");
    }
    if (property->HasAnyPropertyFlags(CPF_DisableEditOnInstance))
    {
        debugPrint += TEXT("|DisableEditOnInstance");
    }
    if (property->HasAnyPropertyFlags(CPF_EditConst))
    {
        debugPrint += TEXT("|EditConst");
    }
    if (property->HasAnyPropertyFlags(CPF_InstancedReference))
    {
        debugPrint += TEXT("|InstancedReference");
    }
    if (property->HasAnyPropertyFlags(CPF_BlueprintAssignable))
    {
        debugPrint += TEXT("|BlueprintAssignable");
    }
    if (property->HasAnyPropertyFlags(CPF_Deprecated))
    {
        debugPrint += TEXT("|Deprecated");
    }
    if (property->HasAnyPropertyFlags(CPF_EditorOnly))
    {
        debugPrint += TEXT("|EditorOnly");
    }
    if (property->HasAnyPropertyFlags(CPF_AutoWeak))
    {
        debugPrint += TEXT("|AutoWeak");
    }
    if (property->HasAnyPropertyFlags(CPF_ContainsInstancedReference))
    {
        debugPrint += TEXT("|ContainsInstancedReference");
    }
    if (property->HasAnyPropertyFlags(CPF_Protected))
    {
        debugPrint += TEXT("|Protected");
    }
    if (property->HasAnyPropertyFlags(CPF_BlueprintCallable))
    {
        debugPrint += TEXT("|BlueprintCallable");
    }
    if (property->HasAnyPropertyFlags(CPF_BlueprintAuthorityOnly))
    {
        debugPrint += TEXT("|BlueprintAuthorityOnly");
    }
    if (property->HasAnyPropertyFlags(CPF_UObjectWrapper))
    {
        debugPrint += TEXT("|UObjectWrapper");
    }
    if (property->HasAnyPropertyFlags(CPF_NativeAccessSpecifierPublic))
    {
        debugPrint += TEXT("|NativeAccessSpecifierPublic");
    }
    if (property->HasAnyPropertyFlags(CPF_NativeAccessSpecifierProtected))
    {
        debugPrint += TEXT("|NativeAccessSpecifierProtected");
    }
    if (property->HasAnyPropertyFlags(CPF_NativeAccessSpecifierPrivate))
    {
        debugPrint += TEXT("|NativeAccessSpecifierPrivate");
    }
    // FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(debugPrint + TEXT("\n"));
}

void InitValueTypeGenerator()
{
    valueTypeRegistry = {};
    invalidTypes = {};
}

ValueTypeBase& ResolveValueType(FProperty* property)
{
    // DebugPrintProp(property);

    FString pureType;
    FString propertyType = GetPropertyType(property, pureType);
    // TODO: check if it's empty

    constexpr auto applyExtraQualifierBeforeReturn =
        [&](ValueTypeBase& baseResult, bool registerBaseResult)
        {
            if (registerBaseResult)
            {
                valueTypeRegistry.Add(pureType, &baseResult);
            }

            auto* result = &baseResult;
            if (property->HasAnyPropertyFlags(CPF_ConstParm))
            {
                auto* qualifier = new ValueTypeQualifier(ValueTypeQualifier::Type::Const);
                qualifier->AddChild(*result);
                result = qualifier;
            }
            if (property->HasAnyPropertyFlags(CPF_OutParm))
            {
                auto* qualifier = new ValueTypeQualifier(ValueTypeQualifier::Type::Out);
                qualifier->AddChild(*result);
                result = qualifier;
            }
            if (property->HasAnyPropertyFlags(CPF_ReferenceParm))
            {
                auto* qualifier = new ValueTypeQualifier(ValueTypeQualifier::Type::Reference);
                qualifier->AddChild(*result);
                result = qualifier;
            }

            return result;
        };

    ValueTypeBase* searchResult = valueTypeRegistry.FindRef(pureType);
    if (searchResult)
    {
        return *applyExtraQualifierBeforeReturn(*searchResult, false);
    }

    ValueTypeBase* result = nullptr;
    if (property->IsA(FClassProperty::StaticClass()))
    {
        auto* classProp = CastField<FClassProperty>(property);
        if (classProp->HasAnyPropertyFlags(CPF_UObjectWrapper))
        {
            // result = new AAGeneratorInitUtilities::UClassValueType(&ResolveValueTypeFromUClass(classProp->MetaClass));
        }
        else
        {
            result = new AAGeneratorInitUtilities::UClassValueType(nullptr);
        }
    }
    else if (property->IsA(FWeakObjectProperty::StaticClass()))
    {
        auto* objectProp = CastField<FWeakObjectProperty>(property);
        auto* objectPtrResult = new ValueTypeQualifier(ValueTypeQualifier::Type::WeakObject);
        objectPtrResult->AddChild(ResolveValueTypeFromUClass(objectProp->PropertyClass));
        result = objectPtrResult;
    }
    else if (property->IsA(FObjectProperty::StaticClass()))
    {
        // TODO: USE CPF_InstancedReference?
        auto* objectProp = CastField<FObjectPropertyBase>(property);
        if (objectProp->HasAnyPropertyFlags(CPF_UObjectWrapper))
        {
            auto* objectPtrResult = new ValueTypeQualifier(ValueTypeQualifier::Type::ObjectPtr);
            objectPtrResult->AddChild(ResolveValueTypeFromUClass(objectProp->PropertyClass));
            result = objectPtrResult;
        }
        else
        {
            result = &ResolveValueTypeFromUClass(objectProp->PropertyClass);
        }
    }
    else if (property->IsA(FArrayProperty::StaticClass()))
    {
        auto* arrayResult = new ValueTypeQualifier(ValueTypeQualifier::Type::Array);
        arrayResult->AddChild(ResolveValueType(CastField<FArrayProperty>(property)->Inner));
        result = arrayResult;
    }
    else if (property->IsA(FMapProperty::StaticClass()))
    {
        // auto* mapResult = new ValueTypeQualifier(ValueTypeQualifier::Type::Map);
        // auto* mapProperty = CastField<FMapProperty>(property);
        // mapResult->AddChild(ResolveValueType(mapProperty->KeyProp));
        // mapResult->AddChild(ResolveValueType(mapProperty->ValueProp));
        // result = mapResult;
    }
    else if (property->IsA(FSetProperty::StaticClass()))
    {
        // auto* setResult = new ValueTypeQualifier(ValueTypeQualifier::Type::Set);
        // setResult->AddChild(ResolveValueType(CastField<FSetProperty>(property)->ElementProp));
        // result = setResult;
    }
    else if (property->IsA(FNumericProperty::StaticClass()))
    {
        auto* numProperty = CastField<FNumericProperty>(property);
        UEnum* propertyEnum = numProperty->GetIntPropertyEnum();
        if (propertyEnum == nullptr)
        {
            result = new PureValueType(PureValueType::Type::BaseType, pureType);
        }
        else
        {
            result = new EnumValueType(propertyEnum);
        }
        // auto* byteProperty = CastField<FByteProperty>(property);
        // if (byteProperty->GetIntPropertyEnum())
    }
    else if (property->IsA(FEnumProperty::StaticClass()))
    {
        result = new EnumValueType(CastField<FEnumProperty>(property)->GetEnum());
    }
    else if (property->IsA(FMulticastDelegateProperty::StaticClass()))
    {
        //
    }
    else if (property->IsA(FBoolProperty::StaticClass()))
    {
        result = new PureValueType(PureValueType::Type::BaseType, pureType);
    }
    else if (property->IsA(FStructProperty::StaticClass()) ||
        property->IsA(FNameProperty::StaticClass()) ||
        property->IsA(FTextProperty::StaticClass()) ||
        property->IsA(FStrProperty::StaticClass()))
    {
        result = new PureValueType(PureValueType::Type::Struct, pureType);
    }

    if (result == nullptr)
    {
        result = new InvalidValueType(pureType);
    }

    return *applyExtraQualifierBeforeReturn(*result, true);
}

bool IsCustomImplementationType(FString name)
{
    return customImplementationTypes.Contains(name);
}

bool IsInvalidType(FString name)
{
    return invalidTypes.Contains(name) || forceInvalidTypes.Contains(name);
}

void FinalizeValueTypeLoad()
{
    // FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(
    //     TEXT("FINALIZE BEGIN\n"));

    FBaseTypeAAGenerator::ConstructAllGenerators();

    for (TObjectIterator<UScriptStruct> It; It; ++It)
    {
        for (const auto& entry : valueTypeRegistry)
        {
            if (ForEachValueType(
                entry.Value,
                AAGeneratorInitUtilities::ValueTypeBase::ClassType::PureValueType,
                [&](const auto* valueType)
                {
                    auto* pureChild = reinterpret_cast<const AAGeneratorInitUtilities::PureValueType*>(valueType);
                    if (pureChild->GetType() == AAGeneratorInitUtilities::PureValueType::Type::Struct &&
                        pureChild->GetName().Compare(FString::Printf(TEXT("%s%s"), It->GetPrefixCPP(), *It->GetName())) == 0 &&
                        !IsCustomImplementationType(pureChild->GetName()) &&
                        !IsInvalidType(pureChild->GetName()))
                    {
                        auto* generator = new FUStructAAGenerator(valueType, *It);
                        if (generator->CanExport())
                        {
                            generator->ExportToMemory();
                            FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().AddGeneratorToMap(generator);
                            FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(TEXT("\nSTRUCT:") + pureChild->GetName());
                        }
                        else
                        {
                            FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(TEXT("\nSTRUCT NOPE:") + pureChild->GetName());
                            delete generator;
                        }

                        return true;
                    }

                    return false;
                }))
            {
                break;
            }
        }
    }

    for (const auto& entry : valueTypeRegistry)
    {
        ForEachValueType(
            entry.Value,
            AAGeneratorInitUtilities::ValueTypeBase::ClassType::EnumValueType,
            [&](const auto* valueType)
            {
                auto* enumValueType = reinterpret_cast<const AAGeneratorInitUtilities::EnumValueType*>(valueType);
                auto* generator = new FEnumAAGenerator(enumValueType->GetEnumData());
                generator->ExportToMemory();
                FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().AddGeneratorToMap(generator);

                return false;
            });
    }

    for (const auto& entry : valueTypeRegistry)
    {
        ForEachValueType(
            entry.Value,
            AAGeneratorInitUtilities::ValueTypeBase::ClassType::PureValueType,
            [&](const auto* valueType)
            {
                auto* pureChild = reinterpret_cast<const AAGeneratorInitUtilities::PureValueType*>(valueType);
                auto* searchResult = FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().GetGenerator(pureChild->GetName());
                if (searchResult == nullptr && !IsCustomImplementationType(pureChild->GetName()))
                {
                    invalidTypes.Add(pureChild->GetName());
                    // FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(
                    //     TEXT("ERROR TYPE ") + pureChild->GetName() + TEXT("|") + entry.Value->GetDebugInfo() + TEXT("\n"));
                }

                return false;
            });
    }

    for (const auto& entry : valueTypeRegistry)
    {
        ForEachValueType(
            entry.Value,
            AAGeneratorInitUtilities::ValueTypeBase::ClassType::ValueTypeQualifier,
            [&](const auto* valueType)
            {
                ValueTypeTreeTraversalContext context(ValueTypeTreeTraversalType::Default);
                auto* qualifier = reinterpret_cast<const AAGeneratorInitUtilities::ValueTypeQualifier*>(valueType);
                if (qualifier->GetType() == ValueTypeQualifier::Type::Array &&
                    qualifier->Supported(context))
                {
                    auto* generator = new TArrayAAGenerator(qualifier);
                    if (generator->CanExport())
                    {
                        generator->ExportToMemory();
                        FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().AddGeneratorToMap(generator);
                    }
                }

                return false;
            });
    }
}

bool CanExportProperty(FProperty* property)
{
    if (property->ArrayDim > 1)
    {
        return false;
    }

    if (property->PropertyFlags & CPF_Deprecated)
    {
        // DebugPrintProp(property);
        return false;
    }

    if (property->PropertyFlags & CPF_NativeAccessSpecifierProtected)
    {
        // DebugPrintProp(property);
        return false;
    }

    if (property->PropertyFlags & CPF_NativeAccessSpecifierPrivate)
    {
        // DebugPrintProp(property);
        return false;
    }

    if (property->GetName().Contains("DEPRECATED"))
    {
        // DebugPrintProp(property);
        return false;
    }

    if (property->PropertyFlags & CPF_EditorOnly)
    {
        // DebugPrintProp(property);
        return false;
    }

    return true;
}

bool CanExportFunction(UFunction* function)
{
    if (function->HasMetaData(TEXT("CustomThunk")))
    {
        return false;
    }

    if (function->HasAnyFunctionFlags(FUNC_EditorOnly) ||
        function->HasAnyFunctionFlags(FUNC_Private) ||
        function->HasAnyFunctionFlags(FUNC_Protected))
    {
        return false;
    }

    if (function->GetName().Contains("DEPRECATED") ||
        function->HasMetaData("Deprecated") ||
        function->HasMetaData("DeprecatedFunction"))
    {
        return false;
    }

    if (function->GetName() == "ExecuteUbergraph")
    {
        return false;
    }

    return true;
}

FString GetPropertyType(FProperty* property, FString& pureTypeOut)
{
    if (!property) // TODO: require CPF_OutParm for now
    {
        return FString("NULL");
    }

    FString innerType;
    FString outerType = property->GetCPPType(&innerType);
    FString result = outerType + innerType;
    result.RemoveSpacesInline();
    pureTypeOut = result;
    if (property->HasAnyPropertyFlags(CPF_ConstParm))
    {
        result = TEXT("const ") + result;
    }

    if (property->HasAnyPropertyFlags(CPF_ReferenceParm))
    {
        result += TEXT("&");
    }
    else if (property->HasAnyPropertyFlags(CPF_OutParm) &&
        !property->HasAnyPropertyFlags(CPF_ReturnParm))
    {
        result += TEXT("&");
    }

    return result;
}

InvalidValueType::InvalidValueType(const FString& type)
    : m_invalidType(type)
{
    //
}

FString InvalidValueType::GetDisplayName() const
{
    return TEXT("<Invalid>");
}

bool InvalidValueType::Supported(ValueTypeTreeTraversalContext& context) const
{
    return false;
}

FString InvalidValueType::GetSourceType(ValueTypeTreeTraversalContext& context) const
{
    return TEXT("INVALID_TYPE<") + m_invalidType + TEXT(">");
}

FString InvalidValueType::GetExportName(ValueTypeTreeTraversalContext& context) const
{
    return TEXT("INVALID_TYPE<") + m_invalidType + TEXT(">");
}

FString InvalidValueType::ConvertToSourceType(ValueTypeTreeTraversalContext& context, const FString& value) const
{
    return TEXT("INVALID TYPE");
}

FString InvalidValueType::ConvertToAAType(ValueTypeTreeTraversalContext& context, const FString& value) const
{
    return TEXT("INVALID TYPE");
}

FString InvalidValueType::GetDebugInfo() const
{
    return TEXT("INVALID ") + m_invalidType;
}

PureValueType::PureValueType(PureValueType::Type type, const FString& name)
    : m_type(type), m_name(name)
{
    //
}

PureValueType::Type PureValueType::GetType() const
{
    return m_type;
}

const FString& PureValueType::GetName() const
{
    return m_name;
}

FString PureValueType::GetDisplayName() const
{
    return m_name.Mid(1);
}

bool PureValueType::Supported(ValueTypeTreeTraversalContext& context) const
{
    switch (m_type)
    {
        case Type::BaseType:
        {
            if (!FBaseTypeAAGenerator::Supported(m_name))
            {
                return false;
            }
        }
        break;

        case Type::Class:
        case Type::Struct:
        {
            if (IsInvalidType(m_name))
            {
                // FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(TEXT("(@INV)"));
                return false;
            }
        }
        break;
    }

    switch (context.GetType())
    {
        case ValueTypeTreeTraversalType::Return:
        {
            if (!context.HasQualifier(ValueTypeQualifier::Type::Const) &&
                context.HasQualifier(ValueTypeQualifier::Type::Out) &&
                context.HasQualifier(ValueTypeQualifier::Type::Reference))
            {
                // FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(TEXT("(@RET)"));
                return false;
            }
        }
        break;

        case ValueTypeTreeTraversalType::InputParam:
        {
            if (!context.HasQualifier(ValueTypeQualifier::Type::Const) &&
                context.HasQualifier(ValueTypeQualifier::Type::Out) &&
                context.HasQualifier(ValueTypeQualifier::Type::Reference))
            {
                // FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(TEXT("(@INP)"));
                return false;
            }
        }
        break;

        case ValueTypeTreeTraversalType::TemplateParam:
        {
            if (context.HasQualifier(ValueTypeQualifier::Type::Const) ||
                context.HasQualifier(ValueTypeQualifier::Type::Out) ||
                context.HasQualifier(ValueTypeQualifier::Type::Reference))
            {
                // FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(TEXT("(@TEMP)"));
                return false;
            }
        }
        break;

        case ValueTypeTreeTraversalType::SetInputType:
        {
            if (m_type == Type::Struct)
            {
                // FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(TEXT("(@setIN)"));
                return false;
            }
        }
        break;
    }

    return true;
}

FString PureValueType::GetSourceType(ValueTypeTreeTraversalContext& context) const
{
    if (context.GetType() == ValueTypeTreeTraversalType::ConversionTemplateParam &&
        m_type == Type::Class)
    {
        return FString::Printf(TEXT("AA%s"), *m_name);
    }
    else
    {
        return m_name;
    }
}

FString PureValueType::GetExportName(ValueTypeTreeTraversalContext& context) const
{
    FString prefix = {};
    FString result = {};
    if (context.GetType() == ValueTypeTreeTraversalType::ConversionTemplateParam)
    {
        switch (m_type)
        {
            case Type::BaseType:
            {
                result = FBaseTypeAAGenerator::GetExportName(m_name);
            }
            break;

            case Type::Class:
            {
                result = FString::Printf(TEXT("AA%s"), *m_name);
            }
            break;

            case Type::Struct:
            {
                result = m_name;
            }
            break;
        }
    }
    else
    {
        switch (m_type)
        {
            case Type::BaseType:
            {
                result = FBaseTypeAAGenerator::GetExportName(m_name);
            }
            break;

            case Type::Class:
            case Type::Struct:
            {
                result = FString::Printf(TEXT("AA%s"), *m_name);
            }
            break;
        }
    }

    switch (context.GetType())
    {
        case ValueTypeTreeTraversalType::Return:
        {
            if (context.HasQualifier(ValueTypeQualifier::Type::Const))
            {
                if (m_type == Type::Class)
                {
                    prefix = TEXT("__CONST__");
                }
                else if (m_type == Type::Struct)
                {
                    // TODO: Figure out how to handle __CREF__ + nullptr check combo
                }
            }
        }
        break;

        case ValueTypeTreeTraversalType::InputParam:
        {
            if (context.HasQualifier(ValueTypeQualifier::Type::Const))
            {
                if (m_type == Type::Class)
                {
                    prefix = TEXT("__CONST__");
                }
                if (m_type == Type::Struct)
                {
                    prefix = TEXT("__CREF__");
                }
            }
            else if (context.HasQualifier(ValueTypeQualifier::Type::Out) &&
                !context.HasQualifier(ValueTypeQualifier::Type::Reference))
            {
                prefix = TEXT("__REF__");
            }
        }
        break;

        case ValueTypeTreeTraversalType::GetReturnType:
        {
            if (m_type == Type::Struct)
            {
                prefix = TEXT("__CREF__");
            }
        }
        break;

        case ValueTypeTreeTraversalType::SetInputType:
        {
            if (m_type == Type::Struct)
            {
                prefix = TEXT("__CREF__");
            }
        }
        break;
    }

    return prefix + result;
}

FString PureValueType::ConvertToSourceType(ValueTypeTreeTraversalContext& context, const FString& value) const
{
    if (context.GetType() == ValueTypeTreeTraversalType::TemplateParam)
    {
        return TEXT("<2SrcConv Not Supported>");
    }

    if (m_type == Type::Struct)
    {
        if (context.GetType() == ValueTypeTreeTraversalType::SetInputType)
        {
            return value + TEXT(".GetConst<") + m_name + TEXT(">()");
        }

        if (context.HasQualifier(ValueTypeQualifier::Type::Const))
        {
            return value + TEXT(".GetConst<") + m_name + TEXT(">()");
        }
        else
        {
            return value + TEXT(".Get<") + m_name + TEXT(">()");
        }
    }
    else
    {
        return value;
    }
}

FString PureValueType::ConvertToAAType(ValueTypeTreeTraversalContext& context, const FString& value) const
{
    if (context.GetType() == ValueTypeTreeTraversalType::TemplateParam)
    {
        return TEXT("<2AAConv Not Supported>");
    }

    if (m_type == Type::Struct)
    {
        if (context.GetType() == ValueTypeTreeTraversalType::Return)
        {
            if (context.HasQualifier(ValueTypeQualifier::Type::Const))
            {
                if (context.HasQualifier(ValueTypeQualifier::Type::Reference))
                {
                    return FString::Printf(TEXT("AA%s::ConvertConst(%s)"), *m_name, *value);
                }
                else
                {
                    return FString::Printf(TEXT("AA%s::ConstructInPlace<%s>(%s)"), *m_name, *m_name, *value);
                }
            }
            else
            {
                if (context.HasQualifier(ValueTypeQualifier::Type::Reference))
                {
                    return FString::Printf(TEXT("AA%s::Const(%s)"), *m_name, *value);
                }
                else
                {
                    return FString::Printf(TEXT("AA%s::ConstructInPlace<%s>(%s)"), *m_name, *m_name, *value);
                }
            }
        }
        else
        {
            // return TEXT("AA") + m_name + TEXT("::ConvertConst(") + value + TEXT(")");
            if (context.HasQualifier(ValueTypeQualifier::Type::Const) ||
                !context.HasQualifier(ValueTypeQualifier::Type::Reference))
            {
                return TEXT("AA") + m_name + TEXT("::ConvertConst(") + value + TEXT(")");
            }
            else
            {
                return TEXT("AA") + m_name + TEXT("::Convert(") + value + TEXT(")");
            }
        }
    }
    else
    {
        return value;
    }
}

FString PureValueType::GetDebugInfo() const
{
    return m_name;
}

EnumValueType::EnumValueType(UEnum* enumData)
    : m_enumData(enumData)
{
    //
}

UEnum* EnumValueType::GetEnumData() const
{
    return m_enumData;
}

FString EnumValueType::GetDisplayName() const
{
    return m_enumData->GetDisplayNameText().ToString();
}

bool EnumValueType::Supported(ValueTypeTreeTraversalContext& context) const
{
    if (m_enumData == nullptr)
    {
        return false;
    }

    switch (context.GetType())
    {
        case ValueTypeTreeTraversalType::Return:
        {
            if (!context.HasQualifier(ValueTypeQualifier::Type::Const) &&
                context.HasQualifier(ValueTypeQualifier::Type::Out)) // &&
                // context.HasQualifier(ValueTypeQualifier::Type::Reference))
            {
                return false;
            }
        }
        break;

        case ValueTypeTreeTraversalType::InputParam:
        {
            if (!context.HasQualifier(ValueTypeQualifier::Type::Const) &&
                context.HasQualifier(ValueTypeQualifier::Type::Out)) // &&
                // context.HasQualifier(ValueTypeQualifier::Type::Reference))
            {
                return false;
            }
        }
        break;

        case ValueTypeTreeTraversalType::TemplateParam:
        {
            if (context.HasQualifier(ValueTypeQualifier::Type::Const) ||
                context.HasQualifier(ValueTypeQualifier::Type::Out) ||
                context.HasQualifier(ValueTypeQualifier::Type::Reference))
            {
                return false;
            }
        }
        break;
    }

    return true;
}

FString EnumValueType::GetSourceType(ValueTypeTreeTraversalContext& context) const
{
    return m_enumData->CppType;
}

FString EnumValueType::GetExportName(ValueTypeTreeTraversalContext& context) const
{
    if (context.GetType() == ValueTypeTreeTraversalType::ConversionTemplateParam)
    {
        if (m_enumData->GetCppForm() == UEnum::ECppForm::EnumClass)
        {
            return m_enumData->CppType;
        }
        else
        {
            return FString::Printf(TEXT("TEnumAsByte<%s>"), *m_enumData->CppType);
        }
    }
    else
    {
        return FEnumAAGenerator::GetExportableName(m_enumData);
    }
}

FString EnumValueType::ConvertToSourceType(ValueTypeTreeTraversalContext& context, const FString& value) const
{
    if (m_enumData->GetCppForm() == UEnum::ECppForm::EnumClass)
    {
        return TEXT("static_cast<") + m_enumData->CppType + TEXT(">(") + value + TEXT(")");
    }
    else
    {
        return TEXT("TEnumAsByte<") + m_enumData->CppType + TEXT(">(static_cast<") + m_enumData->CppType + TEXT(">(") + value + TEXT("))");
    }
}

FString EnumValueType::ConvertToAAType(ValueTypeTreeTraversalContext& context, const FString& value) const
{
    return TEXT("static_cast<") + GetExportName(context) + TEXT(">(static_cast<") + m_enumData->CppType + TEXT(">(") + value + TEXT("))");
}

FString EnumValueType::GetDebugInfo() const
{
    return m_enumData->CppType;
}

ValueTypeQualifier::ValueTypeQualifier(ValueTypeQualifier::Type type)
    : m_type(type)
    , m_childrenTypes()
{
    //
}

void ValueTypeQualifier::AddChild(ValueTypeBase& child)
{
    m_childrenTypes.Add(&child);
}

const TArray<ValueTypeBase*>& ValueTypeQualifier::GetChildren() const
{
    return m_childrenTypes;
}

ValueTypeQualifier::Type ValueTypeQualifier::GetType() const
{
    return m_type;
}

FString ValueTypeQualifier::GetDisplayName() const
{
    return TEXT("vtq");
}

bool ValueTypeQualifier::Supported(ValueTypeTreeTraversalContext& context) const
{
    switch (context.GetType())
    {
        case ValueTypeTreeTraversalType::Return:
        {
            if (context.HasQualifier(ValueTypeQualifier::Type::Const) &&
                !context.HasQualifier(ValueTypeQualifier::Type::Reference))
            {
                return false;
            }
        }
        break;

        case ValueTypeTreeTraversalType::TemplateParam:
        {
            // FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(TEXT("(@NESTED_TP)"));
            return false;
        }
        break;

        case ValueTypeTreeTraversalType::SetInputType:
        {
            return false;
        }
        break;
    }

    if (m_type == Type::SubClass ||
        m_type == Type::ObjectPtr ||
        m_type == Type::WeakObject)
    {
        return false;
    }
    else if (m_type == Type::Array)
    {
        if (m_childrenTypes.Num() != 1)
        {
            // FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(TEXT("(@TP_NUM)"));
            return false;
        }
        else
        {
            ValueTypeTreeTraversalContext subContext(ValueTypeTreeTraversalType::TemplateParam);
            if (m_childrenTypes[0]->Supported(subContext))
            {
                return true;
            }
            else
            {
                // FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(TEXT("(@TP)"));
                return false;
            }
        }
    }
    else
    {
        context.PushQualifier(m_type);
        return std::all_of(m_childrenTypes.begin(), m_childrenTypes.end(), [&](ValueTypeBase* type) { return type->Supported(context); });
    }
}

FString ValueTypeQualifier::GetSourceType(ValueTypeTreeTraversalContext& context) const
{
    if (m_type == Type::Array)
    {
        ValueTypeTreeTraversalContext subContext(ValueTypeTreeTraversalType::ConversionTemplateParam);
        if (m_childrenTypes.Num() == 1)
        {
            return FString::Printf(TEXT("TArray<%s>"), *m_childrenTypes[0]->GetSourceType(subContext));
        }
    }
    else
    {
        context.PushQualifier(m_type);
        if (m_childrenTypes.Num() == 1)
        {
            return m_childrenTypes[0]->GetSourceType(context);
        }
    }

    return TEXT("<INVALID TYPE EXPORT>");
}

FString ValueTypeQualifier::GetExportName(ValueTypeTreeTraversalContext& context) const
{
    if (m_type == Type::Array)
    {
        FString result = {};
        FString prefix = {};

        ValueTypeTreeTraversalContext subContext(ValueTypeTreeTraversalType::TemplateParam);
        if (m_childrenTypes.Num() == 1)
        {
            result = TEXT("AATArrayOf") + m_childrenTypes[0]->GetExportName(subContext);
        }

        switch (context.GetType())
        {
            case ValueTypeTreeTraversalType::Return:
            {
                if (context.HasQualifier(ValueTypeQualifier::Type::Const))
                {
                    prefix = TEXT("__CREF__");
                }
            }
            break;

            case ValueTypeTreeTraversalType::InputParam:
            {
                if (context.HasQualifier(ValueTypeQualifier::Type::Const))
                {
                    prefix = TEXT("__CREF__");
                }
                else if (context.HasQualifier(ValueTypeQualifier::Type::Out) &&
                    !context.HasQualifier(ValueTypeQualifier::Type::Reference))
                {
                    prefix = TEXT("__REF__");
                }
            }
            break;

            case ValueTypeTreeTraversalType::GetReturnType:
            {
                prefix = TEXT("__CREF__");
            }
            break;
        }

        return prefix + result;
    }
    else
    {
        context.PushQualifier(m_type);
        if (m_childrenTypes.Num() == 1)
        {
            return m_childrenTypes[0]->GetExportName(context);
        }
    }

    return TEXT("<INVALID TYPE EXPORT>");
}

FString ValueTypeQualifier::ConvertToSourceType(ValueTypeTreeTraversalContext& context, const FString& value) const
{
    if (m_type == Type::Array)
    {
        ValueTypeTreeTraversalContext subContext(ValueTypeTreeTraversalType::ConversionTemplateParam);
        FString sourceType = FString::Printf(TEXT("TArray<%s>"), *m_childrenTypes[0]->GetExportName(subContext));
        if (context.HasQualifier(ValueTypeQualifier::Type::Const))
        {
            return value + TEXT(".GetConst<") + sourceType + TEXT(">()");
        }
        else
        {
            return value + TEXT(".Get<") + sourceType + TEXT(">()");
        }
    }
    else
    {
        context.PushQualifier(m_type);

        if (m_childrenTypes.Num() == 1)
        {
            return m_childrenTypes[0]->ConvertToSourceType(context, value);
        }
    }

    return TEXT("<INVALID SOURCE TYPE CONVERSION>");
}

FString ValueTypeQualifier::ConvertToAAType(ValueTypeTreeTraversalContext& context, const FString& value) const
{
    if (m_type == Type::Array)
    {
        ValueTypeTreeTraversalContext subContext(ValueTypeTreeTraversalType::Default);
        return GetExportName(subContext) + TEXT("::ConvertConst(") + value + TEXT(")");
    }
    else
    {
        context.PushQualifier(m_type);

        if (m_childrenTypes.Num() == 1)
        {
            return m_childrenTypes[0]->ConvertToAAType(context, value);
        }
    }

    return TEXT("<INVALID AA TYPE CONVERSION>");
}

FString ValueTypeQualifier::GetDebugInfo() const
{
    FString result = {};
    switch (m_type)
    {
        case Type::Const:
        {
            result += TEXT("Const");
        }
        break;

        case Type::Out:
        {
            result += TEXT("Out");
        }
        break;

        case Type::Reference:
        {
            result += TEXT("Ref");
        }
        break;

        case Type::SubClass:
        {
            result += TEXT("SubClass");
        }
        break;

        case Type::ObjectPtr:
        {
            result += TEXT("ObjectPtr");
        }
        break;

        case Type::WeakObject:
        {
            result += TEXT("WeakObject");
        }
        break;

        case Type::Array:
        {
            result += TEXT("Array");
        }
        break;
    }

    result += TEXT("<");
    if (m_childrenTypes.Num() > 0)
    {
        result += m_childrenTypes[0]->GetDebugInfo();
        for (int32 i = 1; i < m_childrenTypes.Num(); ++i)
        {
            result += TEXT(", ") + m_childrenTypes[i]->GetDebugInfo();
        }
    }

    result += TEXT(">");

    return result;
}

UClassValueType::UClassValueType(ValueTypeBase* childType)
    : m_childType(childType)
{
    //
}

FString UClassValueType::GetDisplayName() const
{
    return FString::Printf(
        TEXT("UE Class Type%s"),
        m_childType == nullptr ?
            TEXT("") :
            *FString::Printf(TEXT(" (%s)"), *m_childType->GetDisplayName()));
}

bool UClassValueType::Supported(ValueTypeTreeTraversalContext& context) const
{
    if (m_childType != nullptr && m_childType->GetClassType() != ClassType::PureValueType)
    {
        return false;
    }

    switch (context.GetType())
    {
        case ValueTypeTreeTraversalType::TemplateParam:
        {
            return false;
        }
        break;

        case ValueTypeTreeTraversalType::ConversionTemplateParam:
        {
            return false;
        }
        break;
    }

    if (!context.HasQualifier(ValueTypeQualifier::Type::Const) &&
        context.HasQualifier(ValueTypeQualifier::Type::Out) &&
        context.HasQualifier(ValueTypeQualifier::Type::Reference))
    {
        return false;
    }

    return true;
}

FString UClassValueType::GetSourceType(ValueTypeTreeTraversalContext& context) const
{
    return m_childType == nullptr ?
        TEXT("UClass*") :
        FString::Printf(TEXT("TSubClassOf<%s>"), *reinterpret_cast<const AAGeneratorInitUtilities::PureValueType*>(m_childType)->GetName());
}

FString UClassValueType::GetExportName(ValueTypeTreeTraversalContext& context) const
{
    return TEXT("AAUClass");
}

FString UClassValueType::ConvertToSourceType(ValueTypeTreeTraversalContext& context, const FString& value) const
{
    // return m_childType == nullptr ?
    //     value :
    //     FString::Printf(
    //         TEXT("TSubClassOf<%s>(%s)"),
    //         *reinterpret_cast<const AAGeneratorInitUtilities::PureValueType*>(m_childType)->GetName(),
    //         *value);
    return value;
}

FString UClassValueType::ConvertToAAType(ValueTypeTreeTraversalContext& context, const FString& value) const
{
    // return m_childType == nullptr ?
    //     value :
    //     FString::Printf(
    //         TEXT("TSubClassOf<%s>(%s)"),
    //         *reinterpret_cast<const AAGeneratorInitUtilities::PureValueType*>(m_childType)->GetName(),
    //         *value);
    return value;
}

FString UClassValueType::GetDebugInfo() const
{
    return TEXT("UE Class Type");
}

ValueTypeTreeTraversalContext::ValueTypeTreeTraversalContext(ValueTypeTreeTraversalType type)
    : m_type(type)
{
    //
}

ValueTypeTreeTraversalType ValueTypeTreeTraversalContext::GetType()
{
    return m_type;
}

void ValueTypeTreeTraversalContext::PushQualifier(ValueTypeQualifier::Type type)
{
    m_qualifiers.Add(type);
}

bool ValueTypeTreeTraversalContext::HasQualifier(ValueTypeQualifier::Type type)
{
    for (ValueTypeQualifier::Type qualifier : m_qualifiers)
    {
        if (type == qualifier)
        {
            return true;
        }
    }

    return false;
}

DataMemberExportInfo DataMemberExportInfo::Construct(FProperty *property)
{
    if (property == nullptr)
    {
        return {};
    }
    else
    {
        return
        {
            ResolveValueType(property),
            property->GetName(),
            property->GetDisplayNameText(),
            !property->HasAnyPropertyFlags(CPF_DisableEditOnInstance)
        };
    }
}

bool DataMemberExportInfo::Supported(ValueTypeTreeTraversalType type) const
{
    ValueTypeTreeTraversalContext context(type);
    return m_type != nullptr && m_type->Supported(context);
}

const ValueTypeBase& DataMemberExportInfo::GetType() const
{
    return *m_type;
}

const FString& DataMemberExportInfo::GetName() const
{
    return m_name;
}

bool DataMemberExportInfo::SupportsGet() const
{
    return Supported(ValueTypeTreeTraversalType::GetReturnType);
}

bool DataMemberExportInfo::SupportsSet() const
{
    return m_supportsSet && Supported(ValueTypeTreeTraversalType::SetInputType);
}

bool DataMemberExportInfo::HasDisplayName() const
{
    return !m_displayName.IsEmptyOrWhitespace();
}

const FText& DataMemberExportInfo::GetDisplayName() const
{
    return m_displayName;
}

FString DataMemberExportInfo::GetTypeExport(ValueTypeTreeTraversalType type) const
{
    ValueTypeTreeTraversalContext context(type);
    return GetType().GetExportName(context);
}

FString DataMemberExportInfo::ConvertToSourceType(ValueTypeTreeTraversalType type, const FString& value) const
{
    ValueTypeTreeTraversalContext context(type);
    return GetType().ConvertToSourceType(context, value);
}

FString DataMemberExportInfo::ConvertToAAType(ValueTypeTreeTraversalType type, const FString& value) const
{
    ValueTypeTreeTraversalContext context(type);
    return GetType().ConvertToAAType(context, value);
}

FString DataMemberExportInfo::GetDebugInfo() const
{
    return (m_type == nullptr ? TEXT("NULL") : m_type->GetDebugInfo()) + TEXT(" ") + m_name;
}

DataMemberExportInfo::DataMemberExportInfo() : m_type(nullptr), m_name()
{
    //
}

DataMemberExportInfo::DataMemberExportInfo(
    const ValueTypeBase& type,
    const FString& name,
    const FText& displayName,
    bool supportsSet)
    : m_type(&type)
    , m_name(name)
    , m_displayName(displayName)
    , m_supportsSet(supportsSet)
{
    //
}

FunctionMemberExportInfo FunctionMemberExportInfo::Construct(UClass* uclass, UFunction* function)
{
    UClass* ownerClass = function->GetOwnerClass();
    const bool superClass = ownerClass && ownerClass != uclass;

    if (!superClass && uclass->HasAnyClassFlags(CLASS_MinimalAPI))
    {
        return { function->GetName() };
    }
    else
    {
        FunctionMemberExportInfo result = { function };

        if (superClass)
        {
            result.SetSuperClassName(ownerClass->GetPrefixCPP() + ownerClass->GetName());
        }

        return result;
    }
}

FunctionMemberExportInfo FunctionMemberExportInfo::Construct(UStruct* ustruct, UFunction* function)
{
    FunctionMemberExportInfo result = { function };

    UStruct* ownerStruct = function->GetOwnerStruct();
    if (ownerStruct && ownerStruct != ustruct)
    {
        result.SetSuperClassName(ownerStruct->GetPrefixCPP() + ownerStruct->GetName());
    }

    return result;
}

bool FunctionMemberExportInfo::Supported() const
{
    if (m_name.IsEmpty())
    {
        // FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(TEXT("empty name"));
        return false;
    }

    if (!m_voidReturn &&
        !m_returnType.Supported(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Return))
    {
        // FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(FString::Printf(TEXT("invalid RETURN type [%s]"), *m_returnType.GetDebugInfo()));
        return false;
    }

    if (!std::all_of(
        m_inputParams.begin(),
        m_inputParams.end(),
        [](const auto& entry)
        {
            if (entry.Supported(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::InputParam))
            {
                return true;
            }
            else
            {
                // FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(FString::Printf(TEXT("invalid input '%s' [%s]"), *entry.GetName(), *entry.GetDebugInfo()));
                return false;
            }
        }))
    {
        return false;
    }

    return true;
}

const FString& FunctionMemberExportInfo::GetName() const
{
    return m_name;
}

const FString& FunctionMemberExportInfo::GetCategories() const
{
    return m_categories;
}

const FString& FunctionMemberExportInfo::GetToolTips() const
{
    return m_toolTips;
}

const FString& FunctionMemberExportInfo::GetKeywords() const
{
    return m_keywords;
}

bool FunctionMemberExportInfo::IsStatic() const
{
    return m_static;
}

bool FunctionMemberExportInfo::IsVoidReturn() const
{
    return m_voidReturn;
}

bool FunctionMemberExportInfo::HasSuper() const
{
    return !m_superClassName.IsEmpty();
}

const FString& FunctionMemberExportInfo::GetSuperName() const
{
    return m_superClassName;
}

const DataMemberExportInfo& FunctionMemberExportInfo::GetReturnParam() const
{
    return m_returnType;
}

bool FunctionMemberExportInfo::HasDisplayName() const
{
    return !m_displayName.IsEmptyOrWhitespace();
}

const FText& FunctionMemberExportInfo::GetDisplayName() const
{
    return m_displayName;
}

const TArray<DataMemberExportInfo>& FunctionMemberExportInfo::GetInputParams() const
{
    return m_inputParams;
}

FString FunctionMemberExportInfo::GetDebugInfo() const
{
    FString result = (m_static ? TEXT("STATIC ") : TEXT("(")) +
        m_superClassName + TEXT(")") +
        m_name + TEXT(" -> ") +
        (m_voidReturn ? TEXT("Execution") : m_returnType.GetDebugInfo()) + TEXT(" (\n");
    for (const DataMemberExportInfo& info : m_inputParams)
    {
        result += TEXT("\t") + info.GetDebugInfo() + TEXT(",\n");
    }
    result += TEXT(")\n\n");

    return result;
}

FunctionMemberExportInfo::FunctionMemberExportInfo(const FString& name)
    : m_name(name)
    , m_categories()
    , m_toolTips()
    , m_keywords()
    , m_static(false)
    , m_voidReturn(false)
    , m_superClassName()
    , m_returnType(DataMemberExportInfo::Construct(nullptr))
    , m_inputParams()
{
    //
}

FunctionMemberExportInfo::FunctionMemberExportInfo(UFunction* function)
    : m_name()
    , m_categories()
    , m_toolTips()
    , m_keywords()
    , m_static(false)
    , m_voidReturn(false)
    , m_superClassName()
    , m_returnType(DataMemberExportInfo::Construct(nullptr))
    , m_inputParams()
{
    if (function != nullptr)
    {
        // FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(function->GetName() + TEXT("\n"));

        m_name = function->GetName();
        m_categories = function->GetMetaData(TEXT("Category"));
        m_toolTips = function->GetToolTipText().ToString();
        m_keywords = function->GetMetaData(TEXT("Keywords"));
        m_displayName = function->GetDisplayNameText();
        m_static = function->HasAnyFunctionFlags(FUNC_Static);
        // FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(TEXT("FUNCTION ") + m_name + TEXT("\n"));

        FProperty* returnProperty = function->GetReturnProperty();
        if (returnProperty == nullptr)
        {
            m_voidReturn = true;
            // FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(TEXT("VOID\n"));
        }
        else
        {
            m_returnType = DataMemberExportInfo::Construct(function->GetReturnProperty());

            // DebugPrintProp(function->GetReturnProperty());
        }

        for (TFieldIterator<FProperty> paramIt(function); paramIt; ++paramIt)
        {
            FProperty* param = *paramIt;
            if (!param->HasAnyPropertyFlags(CPF_ReturnParm))
            {
                m_inputParams.Add(DataMemberExportInfo::Construct(param));
                // DebugPrintProp(param);
            }
        }
        // FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(TEXT("FUNCTION ") + m_name + TEXT(" DONE\n"));
    }
}

void FunctionMemberExportInfo::SetSuperClassName(const FString& superClassName)
{
    m_superClassName = superClassName;
}

void ClassExportInfo::Init(const FString& className)
{
    m_className = className;
    m_functionMembers = {};
    m_dataMembers = {};
}

void ClassExportInfo::AddDataMember(const DataMemberExportInfo& dataMemberInfo)
{
    m_dataMembers.Add(dataMemberInfo.GetName(), dataMemberInfo);
}

void ClassExportInfo::AddFunctionMember(const FunctionMemberExportInfo& funcMemberInfo)
{
    m_functionMembers.Add(funcMemberInfo.GetName(), funcMemberInfo);
}

const TMap<FString, FunctionMemberExportInfo>& ClassExportInfo::GetFunctionMembers() const
{
    return m_functionMembers;
}

const TMap<FString, DataMemberExportInfo>& ClassExportInfo::GetDataMembers() const
{
    return m_dataMembers;
}

}
