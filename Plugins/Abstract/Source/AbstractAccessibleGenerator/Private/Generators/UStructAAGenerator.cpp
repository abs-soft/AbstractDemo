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

#include "Generators/UStructAAGenerator.h"

// #include "UnrealType.h"
#include "Templates/Casts.h"
#include "Misc/FileHelper.h"
// #include "UObjectIterator.h"
// #include "ScriptGeneratorManager.h"

#include "AbstractAccessibleGeneratorGlobal.h"


// #include "UStructGenerator.h"
// #include "UnrealType.h"
// #include "Templates/Casts.h"
// #include "Misc/FileHelper.h"
// #include "UObjectIterator.h"

FUStructAAGenerator::FUStructAAGenerator(const AAGeneratorInitUtilities::ValueTypeBase* type, UScriptStruct* scriptStruct)
	: m_type(type)
	, m_scriptStruct(scriptStruct)
{
	// m_LuaFuncReg.Init(GetClassName());
	m_exportInfo.Init(GetClassName());
}

FUStructAAGenerator::~FUStructAAGenerator()
{

}

FString FUStructAAGenerator::GetKey() const
{
	return GetClassName();
}

bool FUStructAAGenerator::CanExport() const
{
	if (m_scriptStruct->HasMetaData("DEPRECATED"))
	{
		return false;
	}

	// if (m_scriptStruct->StructFlags & STRUCT_NoExport)
	// {
	// 	return false;
	// }

	// m_scriptStruct->PrepareCppStructOps();
	// if (m_scriptStruct->GetCppStructOps() == nullptr)
	// {
	// 	return false;
	// }
	// // m_scriptStruct->GetCppStructOps()->GetSize()
	// FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(FString::Printf(TEXT("ASDFASDFASDFASDFASDFASDFASDFASDFASDFASDF %s %d\n"), *GetClassName(), m_scriptStruct->GetCppStructOps()->GetSize()));

	return true;
}

void FUStructAAGenerator::ExportToMemory()
{
	// FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(TEXT("STRUCT ") + GetClassName() + TEXT("\n"));
	ExportDataMembersToMemory();
	// FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(TEXT("STRUCT ") + GetClassName() + TEXT(" DONE\n"));
}

void FUStructAAGenerator::FinalizeMemory()
{
	TArray<const AAGeneratorInitUtilities::DataMemberExportInfo*> makeInputDataMembers = {};
	for (const auto& dataInfoEntry : m_exportInfo.GetDataMembers())
	{
		if (dataInfoEntry.Value.Supported(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Default))
		{
			// TODO: Add check for support
			makeInputDataMembers.Add(&dataInfoEntry.Value);

			if (dataInfoEntry.Value.SupportsGet())
			{
				AAGeneratorInitUtilities::ValueTypeTreeTraversalContext context(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Default);
				AAGeneratorUtilities::NodeDefinitionData nodeDefinition(
					*FString::Printf(TEXT("Get_%s"), *dataInfoEntry.Value.GetName()),
					TEXT("Evaluation"),
					*FString::Printf(TEXT("Get %s of %s"), *dataInfoEntry.Value.GetName(), *m_scriptStruct->GetDisplayNameText().ToString()),
					*FString::Printf(TEXT("Get%s"), *dataInfoEntry.Value.GetName()),
					*m_scriptStruct->GetDisplayNameText().ToString(),
					TEXT(""),
					*FString::Printf(TEXT("Gets the %s property from an instance of %s"), *dataInfoEntry.Value.GetDisplayName().ToString(), *m_scriptStruct->GetDisplayNameText().ToString()),
					*dataInfoEntry.Value.GetTypeExport(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::GetReturnType),
					*FString::Printf(
						TEXT("return %s;\n"),
						*dataInfoEntry.Value.ConvertToAAType(
							AAGeneratorInitUtilities::ValueTypeTreeTraversalType::GetReturnType,
							m_type->ConvertToSourceType(
								context,
								TEXT("Source")) +
							TEXT(".") + dataInfoEntry.Value.GetName())));
				nodeDefinition.AddInputParam(TEXT("Source"), ExportName());
				AddNodeDefinition(nodeDefinition);
			}

			if (dataInfoEntry.Value.SupportsSet())
			{
				AAGeneratorInitUtilities::ValueTypeTreeTraversalContext context(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Default);
				AAGeneratorUtilities::NodeDefinitionData nodeDefinition(
					*FString::Printf(TEXT("Set_%s"), *dataInfoEntry.Value.GetName()),
					TEXT("Execution"),
					*FString::Printf(TEXT("Set %s of %s"), *dataInfoEntry.Value.GetDisplayName().ToString(), *m_scriptStruct->GetDisplayNameText().ToString()),
					*FString::Printf(TEXT("Set%s"), *dataInfoEntry.Value.GetName()),
					*m_scriptStruct->GetDisplayNameText().ToString(),
					TEXT(""),
					*FString::Printf(TEXT("Sets the %s property from an instance of %s"), *dataInfoEntry.Value.GetName(), *m_scriptStruct->GetDisplayNameText().ToString()),
					TEXT("Execution"),
					*FString::Printf(
						TEXT("%s.%s = %s;\n"),
						*m_type->ConvertToSourceType(context, TEXT("Target")),
						*dataInfoEntry.Value.GetName(),
						*dataInfoEntry.Value.ConvertToSourceType(
							AAGeneratorInitUtilities::ValueTypeTreeTraversalType::SetInputType,
							TEXT("NewValue"))));
				nodeDefinition.AddInputParam(TEXT("Target"), ExportName());
				nodeDefinition.AddInputParam(TEXT("NewValue"), dataInfoEntry.Value.GetTypeExport(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::SetInputType));
				AddNodeDefinition(nodeDefinition);
			}
		}
	}

	if (makeInputDataMembers.Num() < 50)
	{
		AAGeneratorInitUtilities::ValueTypeTreeTraversalContext context0(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Default);
		AAGeneratorInitUtilities::ValueTypeTreeTraversalContext context1(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Default);

		FString makeNodeDefinitionBody = {};
		makeNodeDefinitionBody +=
			FString::Printf(
				TEXT("%s result = {};\nnew (&result) %s();\n"),
				*ExportName(),
				*m_type->GetSourceType(context1));
		for (const auto* makeInput : makeInputDataMembers)
		{
			makeNodeDefinitionBody +=
				FString::Printf(
					TEXT("%s.%s = %s;\n"),
					*m_type->ConvertToSourceType(
						context0,
						TEXT("result")),
					*makeInput->GetName(),
					*makeInput->ConvertToSourceType(
						AAGeneratorInitUtilities::ValueTypeTreeTraversalType::SetInputType,
						TEXT("_") + makeInput->GetName()));
		}

		makeNodeDefinitionBody += TEXT("return result;\n");

		AAGeneratorUtilities::NodeDefinitionData nodeDefinition(
			FString::Printf(TEXT("Make%s"), *ExportName()),
			TEXT("Evaluation"),
			FString::Printf(TEXT("Make %s"), *m_scriptStruct->GetDisplayNameText().ToString()),
			FString::Printf(TEXT("Make%s"), *ExportName()),
			*m_scriptStruct->GetDisplayNameText().ToString(),
			TEXT(""),
			FString::Printf(TEXT("Make an instance of %s"), *m_scriptStruct->GetDisplayNameText().ToString()),
			*ExportName(),
			*makeNodeDefinitionBody);
		for (const auto* makeInput : makeInputDataMembers)
		{
			nodeDefinition.AddInputParam(TEXT("_") + makeInput->GetName(), makeInput->GetTypeExport(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::SetInputType));
		}
		AddNodeDefinition(nodeDefinition);
	}
}

FString FUStructAAGenerator::GetClassName() const
{
	return FString::Printf(TEXT("%s%s"), m_scriptStruct->GetPrefixCPP(), *m_scriptStruct->GetName());
}

FString FUStructAAGenerator::ExportName() const
{
	return TEXT("AA") + GetClassName();
}

FString FUStructAAGenerator::ExportHeaderContent() const
{
	return {};
}

FString FUStructAAGenerator::ExportConversionRules() const
{
	return {};
}

FString FUStructAAGenerator::ExportTypeDeclarations() const
{
	// TODO: GetStructureSize() can be incorrect so CppStructOps need to be used to get the correct size
	const int32 structSize = m_scriptStruct->GetStructureSize();
	return FString::Printf(
		TEXT("ABSTRACT_SDK_VALUE_TYPE_DEFINITION_SIZED_EXTERN(ABS_SDK_PROPERTIES(DisplayText = \"%s\", ScriptName = \"%s\"), %s, %d);\n"),
		*m_scriptStruct->GetDisplayNameText().ToString(),
		*m_scriptStruct->GetName(),
		*ExportName(),
		structSize > 8 ?
			(structSize > 16 ?
				4096 :
				structSize) :
			8);
}

bool FUStructAAGenerator::RequiresImplementation() const
{
	return true;
}

FString FUStructAAGenerator::ExportAdditionalIncludeDirectives() const
{
	return {};
}

void FUStructAAGenerator::ExportDataMembersToMemory()
{
	for (TFieldIterator<FProperty> propertyIt(m_scriptStruct /*, EFieldIteratorFlags::ExcludeSuper*/); propertyIt; ++propertyIt)
	{
		FProperty* pProperty = *propertyIt;
		AAGeneratorInitUtilities::DataMemberExportInfo dataMemberInfo =
			AAGeneratorInitUtilities::DataMemberExportInfo::Construct(pProperty);
		if (AAGeneratorInitUtilities::CanExportProperty(pProperty))
		{
			m_exportInfo.AddDataMember(dataMemberInfo);
		}
	}
}

// void FUStructAAGenerator::ExportDataMemberToMemory()
// {
// }

// void FUStructAAGenerator::ExportFunctionsToMemory()
// {
// 	for (TFieldIterator<UFunction> FuncIt(m_pScriptStruct /*, EFieldIteratorFlags::ExcludeSuper*/); FuncIt; ++FuncIt)
// 	{
// 		UFunction* Function = *FuncIt;
// 		if (NS_LuaGenerator::CanExportFunction(Function) && CanExportFunction(Function) && FExportFuncMemberInfo::CanExportFunction(Function))
// 		{
// 			m_LuaFuncReg.AddFunctionMember(FExportFuncMemberInfo::CreateFunctionMemberInfo(m_pScriptStruct, Function));
// 		}
// 	}
// }

// void FUStructAAGenerator::ExportExtraFuncsToMemory()
// {
// 	m_LuaFuncReg.AddExtraFuncMember(GenerateNewExportFunction());
// 	m_LuaFuncReg.AddExtraFuncMember(GenerateDestoryExportFunction());
// }

// bool FUStructAAGenerator::CanExportFunction(UFunction *InFunction)
// {
// 	FExportConfig *pConfig = g_LuaConfigManager->ExportConfig.Find(GetClassName());
// 	if (pConfig && pConfig->NotExportFunctions.Contains(InFunction->GetName()))
// 	{
// 		return false;
// 	}

// 	return true;
// }

// bool FUStructAAGenerator::CanExportProperty(UProperty *InProperty)
// {
// 	return true;
// }

// FString FUStructAAGenerator::GetFuncContents()
// {
// 	return m_LuaFuncReg.GetFuncContents();
// }

// FString FUStructAAGenerator::GetRegContents()
// {
// 	return m_LuaFuncReg.GetRegLibContents();
// }

// FExtraFuncMemberInfo FUStructAAGenerator::GenerateNewExportFunction()
// {
// 	FExtraFuncMemberInfo ExtraFuncNew;
// 	ExtraFuncNew.funcName = "New";
// 	FString &funcBody = ExtraFuncNew.funcBody;
// 	funcBody += EndLinePrintf(TEXT("\t%s *pStruct = new %s;"), *GetClassName(), *GetClassName());
// 	funcBody += EndLinePrintf(TEXT("\tFLuaUtil::Push(InLuaState, FLuaClassType<%s*>(pStruct, \"%s\"));"), *GetClassName(), *GetClassName());
// 	funcBody += EndLinePrintf(TEXT("\treturn 1;"));

// 	return ExtraFuncNew;
// }

// FExtraFuncMemberInfo FUStructAAGenerator::GenerateDestoryExportFunction()
// {
// 	FExtraFuncMemberInfo ExtraFuncDestory;
// 	ExtraFuncDestory.funcName = "Destory";
// 	FString &funcBody = ExtraFuncDestory.funcBody;
// 	funcBody += EndLinePrintf(TEXT("\t%s *pStruct = FLuaUtil::TouserData<%s*>(InLuaState, 1, \"%s\");"), *GetClassName(), *GetClassName(), *GetClassName());
// 	funcBody += EndLinePrintf(TEXT("\tif(pStruct) delete pStruct;"));
// 	funcBody += EndLinePrintf(TEXT("\tpStruct = nullptr;"));
// 	funcBody += EndLinePrintf(TEXT("\treturn 0;"));
// 	return ExtraFuncDestory;
// }


FString FUStructAAGenerator::ExportBlueprintFunctionLibraryForwardDecl() const
{
	return {};
}

FString FUStructAAGenerator::ExportBlueprintFunctionLibraryDeclarations() const
{
	return {};
}

FString FUStructAAGenerator::ExportBlueprintFunctionLibraryDefinitions() const
{
	return {};
}
