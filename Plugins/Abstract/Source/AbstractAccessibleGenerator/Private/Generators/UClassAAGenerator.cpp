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

#include "Generators/UClassAAGenerator.h"

// #include "UnrealType.h"
#include "Templates/Casts.h"
#include "Misc/FileHelper.h"
// #include "UObjectIterator.h"
// #include "ScriptGeneratorManager.h"

#include "AbstractAccessibleGeneratorGlobal.h"
#include "Generators/AAGeneratorInitUtilities.h"

namespace
{
	TSet<FString> exportedNames = {};

	TSet<FString> noCastingNodes =
	{
		// Due to unkonwn LNK2019 unresolved external symbol issue
		"UEngineBaseTypes",
		"UActorComponentInstanceDataTransientOuter",
		"UActorContainer",
		"UDEPRECATED_Breakpoint",
		"UPendingNetGame",
		"UScriptViewportClient",
		"UScene",
		"UListViewDesignerPreviewItem",
		"USlateAccessibleWidgetData",
		"UNavTestRenderingComponent",
		"ADetourCrowdAIController",
		"AGridPathAIController",
		"UAIDataProvider_Random",
		"UEnvQueryTest_Distance",
		"UEnvQueryTest_PathfindingBatch",
		"UObjectTraceWorldSubsystem",
		"UAnimStateMachineTypes",
		"UDEPRECATED_CurveEdPresetCurve",
		"UHLODProxyDesc",
		"USMInstanceElementIdMapTransactor",
		"USoundGroups",
		"UInterpFilter",
		"ULevelInstanceEditorObject",
		"UObjectReferencer",
		"UParticleModuleOrientationBase",
		"UParticleModuleEventSendToGame",
		"UParticleSystemReplay",
		"UReporterBase",
		"URPCDoSDetectionConfig",
		"UTextPropertyTestObject",
		"URuntimeVirtualTextureStreamingProxy",
		"UVirtualTexture2D",
		"UVisualLoggerAutomationTests",
		"UWorldPartitionEditorCell",
		"UWorldPartitionRuntimeCell",
		"UWorldPartitionStreamingPolicy",
		"ABandwidthTestActor",
		"AParticleEventManager",
		"UCameraLensEffectInterfaceClassSupportLibrary",
		"UWorldPartitionRuntimeSpatialHashCell",
		"ASpatialHashRuntimeGridInfo",
		"APhysicsThruster",
		"UAnimCompress_LeastDestructive",
		"UAnimCompress_PerTrackCompression",
		"UAsyncActionLoadPrimaryAssetBase",
		"UAnimationAssetExtensions",
		"UBuiltInAttributesExtensions",
		"UPluginCommandlet",
		"USmokeTestCommandlet",
		"UInterpFilter_Classes",
		"UInterpGroupInstCamera",
		"UInterpTrackFade",
		"UInterpTrackFloatAnimBPParam",
		"UInterpTrackFloatParticleParam",
		"UInterpTrackSlomo",
		"UInterpTrackColorScale",
		"UInterpTrackInstAudioMaster",
		"UInterpTrackInstColorScale",
		"UInterpTrackInstFade",
		"UInterpTrackInstFloatAnimBPParam",
		"UInterpTrackInstFloatMaterialParam",
		"UInterpTrackInstFloatParticleParam",
		"UInterpTrackInstParticleReplay",
		"UInterpTrackInstProperty",
		"UInterpTrackInstSlomo",
		"UInterpTrackInstSound",
		"UInterpTrackInstToggle",
		"UInterpTrackInstVectorMaterialParam",
		"UInterpTrackInstVisibility",
		"UInterpTrackInstBoolProp",
		"UInterpTrackInstColorProp",
		"UInterpTrackInstLinearColorProp",
		"UInterpTrackInstVectorProp",
		"ULevelStreamingPersistent",
		"UWorldPartitionRuntimeLevelStreamingCell",
		"UMaterialExpressionActorPositionWS",
		"UMaterialExpressionArccosineFast",
		"UMaterialExpressionArcsineFast",
		"UMaterialExpressionArctangent2Fast",
		"UMaterialExpressionArctangentFast",
		"UMaterialExpressionAtmosphericFogColor",
		"UMaterialExpressionAtmosphericLightColor",
		"UMaterialExpressionAtmosphericLightVector",
		"UMaterialExpressionCloudSampleAttribute",
		"UMaterialExpressionDBufferTexture",
		"UMaterialExpressionDecalDerivative",
		"UMaterialExpressionDecalLifetimeOpacity",
		"UMaterialExpressionDecalMipmapLevel",
		"UMaterialExpressionDeltaTime",
		"UMaterialExpressionDepthFade",
		"UMaterialExpressionDepthOfFieldFunction",
		"UMaterialExpressionDeriveNormalZ",
		"UMaterialExpressionDistanceCullFade",
		"UMaterialExpressionDistanceFieldGradient",
		"UMaterialExpressionDistanceFieldsRenderingSwitch",
		"UMaterialExpressionDistanceToNearestSurface",
		"UMaterialExpressionEyeAdaptation",
		"UMaterialExpressionEyeAdaptationInverse",
		"UMaterialExpressionGIReplace",
		"UMaterialExpressionLightmapUVs",
		"UMaterialExpressionLightmassReplace",
		"UMaterialExpressionLightVector",
		"UMaterialExpressionMapARPassthroughCameraUV",
		"UMaterialExpressionMaterialProxyReplace",
		"UMaterialExpressionObjectBounds",
		"UMaterialExpressionObjectPositionWS",
		"UMaterialExpressionObjectRadius",
		"UMaterialExpressionParticleColor",
		"UMaterialExpressionParticleDirection",
		"UMaterialExpressionParticleMacroUV",
		"UMaterialExpressionParticleMotionBlurFade",
		"UMaterialExpressionParticlePositionWS",
		"UMaterialExpressionParticleRadius",
		"UMaterialExpressionParticleRandom",
		"UMaterialExpressionParticleRelativeTime",
		"UMaterialExpressionParticleSize",
		"UMaterialExpressionParticleSpeed",
		"UMaterialExpressionPathTracingQualitySwitch",
		"UMaterialExpressionPerInstanceCustomData",
		"UMaterialExpressionPerInstanceCustomData3Vector",
		"UMaterialExpressionPerInstanceFadeAmount",
		"UMaterialExpressionPerInstanceRandom",
		"UMaterialExpressionPrecomputedAOMask",
		"UMaterialExpressionPreSkinnedLocalBounds",
		"UMaterialExpressionRayTracingQualitySwitch",
		"UMaterialExpressionReflectionCapturePassSwitch",
		"UMaterialExpressionRotator",
		"UMaterialExpressionRound",
		"UMaterialExpressionRuntimeVirtualTextureReplace",
		"UMaterialExpressionSamplePhysicsVectorField",
		"UMaterialExpressionSamplePhysicsScalarField",
		"UMaterialExpressionSamplePhysicsIntegerField",
		"UMaterialExpressionSceneColor",
		"UMaterialExpressionSceneDepth",
		"UMaterialExpressionSceneDepthWithoutWater",
		"UMaterialExpressionSceneTexelSize",
		"UMaterialExpressionSceneTexture",
		"UMaterialExpressionScreenPosition",
		"UMaterialExpressionShadowReplace",
		"UMaterialExpressionSign",
		"UMaterialExpressionSkyAtmosphereLightIlluminance",
		"UMaterialExpressionSkyAtmosphereLightDiskLuminance",
		"UMaterialExpressionSkyAtmosphereAerialPerspective",
		"UMaterialExpressionSkyAtmosphereDistantLightScatteredLuminance",
		"UMaterialExpressionSkyAtmosphereLightDirection",
		"UMaterialExpressionSkyAtmosphereViewLuminance",
		"UMaterialExpressionSkyLightEnvMapSample",
		"UMaterialExpressionSphericalParticleOpacity",
		"UMaterialExpressionTruncate",
		"UMaterialExpressionViewSize",
		"UMaterialExpressionVirtualTextureFeatureSwitch",
		"UMaterialExpressionVolumetricAdvancedMaterialInput",
		"UMaterialExpressionBentNormalCustomOutput",
		"UMaterialExpressionRuntimeVirtualTextureOutput",
		"UParticleModuleAccelerationBase",
		"UParticleModuleAttractorBase",
		"UParticleModuleBeamBase",
		"UParticleModuleCameraBase",
		"UParticleModuleCollisionBase",
		"UParticleModuleEventBase",
		"UParticleModuleKillBase",
		"UParticleModuleLifetimeBase",
		"UParticleModuleLightBase",
		"UParticleModuleMaterialBase",
		"UParticleModuleOrbitBase",
		"UParticleModuleParameterBase",
		"UParticleModuleRotationBase",
		"UParticleModuleRotationRateBase",
		"UParticleModuleSizeBase",
		"UParticleModuleSpawnBase",
		"UParticleModuleSubUVBase",
		"UParticleModuleTrailBase",
		"UParticleModuleVectorFieldBase",
		"UParticleModuleVelocityBase",
		"UParticleModuleAttractorPointGravity",
		"UParticleModuleBeamModifier",
		"UParticleModuleColor_Seeded",
		"UParticleModuleEventReceiverBase",
		"UParticleModuleEventReceiverKillParticles",
		"UParticleModuleEventReceiverSpawn",
		"UParticleModuleKillBox",
		"UParticleModuleKillHeight",
		"UParticleModuleLifetime_Seeded",
		"UParticleModuleParameterDynamic_Seeded",
		"UParticleModuleMeshRotation_Seeded",
		"UParticleModuleRotation_Seeded",
		"UParticleModuleMeshRotationRateMultiplyLife",
		"UParticleModuleMeshRotationRateOverLife",
		"UParticleModuleMeshRotationRate_Seeded",
		"UParticleModuleRotationRate_Seeded",
		"UParticleModuleSize_Seeded",
		"UParticleModuleVectorFieldGlobal",
		"UParticleModuleVectorFieldRotation",
		"UParticleModuleVelocity_Seeded",
		"UDemoPendingNetGame",
		"UCloudStorageBase",
		"UInGameAdManager",
		"UMicroTransactionBase",
		"UTwitterIntegrationBase",
		"UDialogueSoundWaveProxy",
		"USoundNodeDoppler",
		"USoundNodeOscillator",
		"UAutoDestroySubsystem",
		"UWorldPartitionLevelStreamingPolicy"
	};
}

void FUClassAAGenerator::RegisterNew(FUClassAAGenerator* generator)
{
	if (generator)
	{
		if (generator->CanExport())
		{
			exportedNames.Add(generator->ExportName());
		}
	}
}

FUClassAAGenerator::FUClassAAGenerator(UClass* ulass, const FString& headerFileName)
	: m_uclass(ulass)
	, m_headerFilepath(headerFileName)
{
	m_exportInfo.Init(GetClassName());
}

FUClassAAGenerator::~FUClassAAGenerator()
{

}

bool FUClassAAGenerator::CanExport() const
{
	if (m_uclass->HasAnyClassFlags(CLASS_Interface))
	{
		return false;
	}

	if (m_headerFilepath.IsEmpty())
	{
		return false;
	}

	UClass* superClass = m_uclass;
	while (superClass != nullptr)
	{
		FString superClassName = FString::Printf(TEXT("%s%s"), superClass->GetPrefixCPP(), *superClass->GetName());
		if (superClassName == TEXT("UProperty"))
		{
			return false;
		}

		superClass = superClass->GetSuperClass();
	}

	return true;
}

void FUClassAAGenerator::ExportToMemory()
{
	// FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(TEXT("CLASS ") + GetClassName() + TEXT("\n"));
	ExportDataMembersToMemory();
	ExportFunctionMembersToMemory();
	// FAbstractAccessibleGeneratorGlobal::GetGeneratorManager().PropertyTypeAAInternal.Add(TEXT("CLASS ") + GetClassName() + TEXT(" DONE\n"));
}

void FUClassAAGenerator::FinalizeMemory()
{
	if (m_uclass && !noCastingNodes.Contains(GetClassName()))
	{
		bool uobjectFound = false;
		TArray<UClass*> superClasses = {};

		{
			UClass* superClass = m_uclass->GetSuperClass();
			while (superClass != nullptr)
			{
				uobjectFound = uobjectFound || superClass == UObject::StaticClass();
				superClasses.Add(superClass);

				FString superClassName = FString::Printf(TEXT("%s%s"), superClass->GetPrefixCPP(), *superClass->GetName());
				FString superClassExportName = FString::Printf(TEXT("AA%s"), *superClassName);
				if (!exportedNames.Contains(superClassExportName))
				{
					break;
				}

				superClass = superClass->GetSuperClass();
			}
		}

		if (uobjectFound)
		{
			for (UClass* superClass : superClasses)
			{
				FString superClassName = FString::Printf(TEXT("%s%s"), superClass->GetPrefixCPP(), *superClass->GetName());
				FString superClassExportName = FString::Printf(TEXT("AA%s"), *superClassName);
				AAGeneratorUtilities::NodeDefinitionData castNodeDefinition(
					*FString::Printf(TEXT("CastTo%s"), *GetClassName()),
					TEXT("Evaluation"),
					*FString::Printf(TEXT("Cast to %s"), *m_uclass->GetDisplayNameText().ToString()),
					*FString::Printf(TEXT("CastTo%s"), *ExportName()),
					*m_uclass->GetDisplayNameText().ToString(),
					TEXT("cast class type"),
					*FString::Printf(TEXT("Casts an instance of %s to %s"), *superClass->GetDisplayNameText().ToString(), *m_uclass->GetDisplayNameText().ToString()),
					*ExportName(),
					*FString::Printf(TEXT("return Cast<%s>(Target);\n"), *GetClassName()));
				castNodeDefinition.AddInputParam(TEXT("Target"), superClassExportName);
				AddNodeDefinition(castNodeDefinition);

				AAGeneratorUtilities::NodeDefinitionData checkTypeNodeDefinition(
					*FString::Printf(TEXT("Is%s"), *GetClassName()),
					TEXT("Evaluation"),
					*FString::Printf(TEXT("Is %s"), *m_uclass->GetDisplayNameText().ToString()),
					*FString::Printf(TEXT("Is%s"), *ExportName()),
					*m_uclass->GetDisplayNameText().ToString(),
					TEXT("is class type"),
					*FString::Printf(TEXT("Checks if an instance of %s is also an instance of %s"), *superClass->GetDisplayNameText().ToString(), *m_uclass->GetDisplayNameText().ToString()),
					TEXT("AABBool"),
					*FString::Printf(TEXT("return Target == nullptr ? false : Target->IsA<%s>();\n"), *GetClassName()));
				checkTypeNodeDefinition.AddInputParam(TEXT("Target"), superClassExportName);
				AddNodeDefinition(checkTypeNodeDefinition);
			}
		}
	}

	for (const auto& dataInfoEntry : m_exportInfo.GetDataMembers())
	{
		if (dataInfoEntry.Value.Supported(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Default))
		{
			if (dataInfoEntry.Value.SupportsGet())
			{
				AAGeneratorUtilities::NodeDefinitionData nodeDefinition(
					*FString::Printf(TEXT("Get_%s"), *dataInfoEntry.Value.GetName()),
					TEXT("Evaluation"),
					*FString::Printf(TEXT("Get %s of %s"), *dataInfoEntry.Value.GetName(), *m_uclass->GetDisplayNameText().ToString()),
					*FString::Printf(TEXT("Get%s"), *dataInfoEntry.Value.GetName()),
					*m_uclass->GetDisplayNameText().ToString(),
					TEXT(""),
					*FString::Printf(TEXT("Gets the %s property from an instance of %s"), *dataInfoEntry.Value.GetDisplayName().ToString(), *m_uclass->GetDisplayNameText().ToString()),
					*dataInfoEntry.Value.GetTypeExport(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::GetReturnType),
					*FString::Printf(
						TEXT("return %s;\n"),
						*dataInfoEntry.Value.ConvertToAAType(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::GetReturnType, TEXT("Source->") + dataInfoEntry.Value.GetName())));
				nodeDefinition.AddInputParam(TEXT("Source"), ExportName());
				AddNodeDefinition(nodeDefinition);
			}

			if (dataInfoEntry.Value.SupportsSet())
			{
				AAGeneratorUtilities::NodeDefinitionData nodeDefinition(
					*FString::Printf(TEXT("Set_%s"), *dataInfoEntry.Value.GetName()),
					TEXT("Execution"),
					*FString::Printf(TEXT("Set %s of %s"), *dataInfoEntry.Value.GetDisplayName().ToString(), *m_uclass->GetDisplayNameText().ToString()),
					*FString::Printf(TEXT("Set%s"), *dataInfoEntry.Value.GetName()),
					*m_uclass->GetDisplayNameText().ToString(),
					TEXT(""),
					*FString::Printf(TEXT("Sets the %s property from an instance of %s"), *dataInfoEntry.Value.GetName(), *m_uclass->GetDisplayNameText().ToString()),
					TEXT("Execution"),
					*FString::Printf(
						TEXT("if (Target)\nTarget->%s = %s;\n"),
						*dataInfoEntry.Value.GetName(),
						*dataInfoEntry.Value.ConvertToSourceType(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::SetInputType, TEXT("NewValue"))));
				nodeDefinition.AddInputParam(TEXT("Target"), ExportName());
				nodeDefinition.AddInputParam(TEXT("NewValue"), dataInfoEntry.Value.GetTypeExport(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::SetInputType));
				AddNodeDefinition(nodeDefinition);
			}
		}
	}

	for (const auto& functionInfoEntry : m_exportInfo.GetFunctionMembers())
	{
		if (functionInfoEntry.Value.Supported())
		{
			AAGeneratorInitUtilities::ValueTypeTreeTraversalContext returnTypeTraversalContext(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Return);
			if (!functionInfoEntry.Value.IsVoidReturn())
			{
				functionInfoEntry.Value.GetReturnParam().GetType().GetExportName(returnTypeTraversalContext);
			}
			const bool isNotRefReturn = !returnTypeTraversalContext.HasQualifier(AAGeneratorInitUtilities::ValueTypeQualifier::Type::Reference);

			FString functionImplementation = {};
			if (functionInfoEntry.Value.IsStatic())
			{
				if (!functionInfoEntry.Value.IsVoidReturn())
				{
					functionImplementation += TEXT("return ");
				}

				FString subResult = {};
				subResult += GetClassName() + TEXT("::") + functionInfoEntry.Value.GetName() + TEXT("(");
				bool skippedFirstComma = false;
				for (const auto& inputParamInfo : functionInfoEntry.Value.GetInputParams())
				{
					if (skippedFirstComma)
					{
						subResult += TEXT(", ");
					}
					else
					{
						skippedFirstComma = true;
					}

					subResult += inputParamInfo.ConvertToSourceType(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::InputParam, inputParamInfo.GetName());
				}
				subResult += TEXT(")");

				if (!functionInfoEntry.Value.IsVoidReturn())
				{
					subResult = functionInfoEntry.Value.GetReturnParam().ConvertToAAType(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Return, subResult);
				}

				functionImplementation += subResult + TEXT(";\n");
			}
			else
			{
				if (isNotRefReturn)
				{
					functionImplementation += TEXT("if (Target)\n{\n");
				}

				if (!functionInfoEntry.Value.IsVoidReturn())
				{
					functionImplementation += TEXT("return ");
				}

				FString subResult = {};
				subResult += TEXT("Target->") + functionInfoEntry.Value.GetName() + TEXT("(");
				bool skippedFirstComma = false;
				for (const auto& inputParamInfo : functionInfoEntry.Value.GetInputParams())
				{
					if (skippedFirstComma)
					{
						subResult += TEXT(", ");
					}
					else
					{
						skippedFirstComma = true;
					}

					subResult += inputParamInfo.ConvertToSourceType(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::InputParam, inputParamInfo.GetName());
				}
				subResult += TEXT(")");

				if (!functionInfoEntry.Value.IsVoidReturn())
				{
					subResult = functionInfoEntry.Value.GetReturnParam().ConvertToAAType(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Return, subResult);
				}
				functionImplementation += subResult + TEXT(";\n");

				if (isNotRefReturn)
				{
					functionImplementation += TEXT("}\n");
				}
			}

			if (!functionInfoEntry.Value.IsVoidReturn() && isNotRefReturn)
			{
				functionImplementation += TEXT("return {};\n");
			}

			AAGeneratorUtilities::NodeDefinitionData nodeDefinition(
				*functionInfoEntry.Value.GetName(),
				TEXT("Execution"),
				*functionInfoEntry.Value.GetDisplayName().ToString(),
				*functionInfoEntry.Value.GetName(),
				*functionInfoEntry.Value.GetCategories(),
				*functionInfoEntry.Value.GetKeywords(),
				*functionInfoEntry.Value.GetToolTips(),
				functionInfoEntry.Value.IsVoidReturn() ?
				TEXT("Execution") :
				*functionInfoEntry.Value.GetReturnParam().GetTypeExport(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::Return),
				functionImplementation);

			if (!functionInfoEntry.Value.IsStatic())
			{
				nodeDefinition.AddInputParam(TEXT("Target"), ExportName());
			}

			for (const auto& inputParamInfo : functionInfoEntry.Value.GetInputParams())
			{
				nodeDefinition.AddInputParam(inputParamInfo.GetName(), inputParamInfo.GetTypeExport(AAGeneratorInitUtilities::ValueTypeTreeTraversalType::InputParam));
			}

			AddNodeDefinition(nodeDefinition);
		}
	}
}

FString FUClassAAGenerator::GetClassName() const
{
	return FString::Printf(TEXT("%s%s"), m_uclass->GetPrefixCPP(), *m_uclass->GetName());
}

FString FUClassAAGenerator::ExportName() const
{
	return TEXT("AA") + GetClassName();
}

FString FUClassAAGenerator::ExportHeaderContent() const
{
	return TEXT("class ") + GetClassName() + TEXT(";\n");
}

FString FUClassAAGenerator::ExportConversionRules() const
{
	FString result = {};
	if (m_uclass)
	{
		UClass* superClass = m_uclass->GetSuperClass();
		while (superClass != nullptr)
		{
			FString superClassExportName = FString::Printf(TEXT("AA%s%s"), superClass->GetPrefixCPP(), *superClass->GetName());
			if (exportedNames.Contains(superClassExportName))
			{
				result += TEXT("ABSTRACT_SDK_VALUE_TYPE_CONVERSION_RULE_EXTERN(") + ExportName() + TEXT(", ") + superClassExportName + TEXT(");\n");
			}
			else
			{
				break;
			}
			superClass = superClass->GetSuperClass();
		}
	}

	return result;
}

FString FUClassAAGenerator::ExportTypeDeclarations() const
{
	return FString::Printf(
		TEXT("ABSTRACT_SDK_VALUE_TYPE_DEFINITION_EXTERN(ABS_SDK_PROPERTIES(DisplayText = \"%s\", ScriptName = \"%s\"), %s, %s*);\n"),
		*m_uclass->GetDisplayNameText().ToString(),
		*m_uclass->GetName(),
		*ExportName(),
		*GetClassName());
}

bool FUClassAAGenerator::RequiresImplementation() const
{
	return true;
}

FString FUClassAAGenerator::ExportAdditionalIncludeDirectives() const
{
	return TEXT("#include \"") + m_headerFilepath + TEXT("\"\n");
}

void FUClassAAGenerator::ExportDataMembersToMemory()
{
	for (TFieldIterator<FProperty> PropertyIt(m_uclass, EFieldIteratorFlags::ExcludeSuper); PropertyIt; ++PropertyIt)
	{
		FProperty* pProperty = *PropertyIt;
		AAGeneratorInitUtilities::DataMemberExportInfo dataMemberInfo =
			AAGeneratorInitUtilities::DataMemberExportInfo::Construct(pProperty);
		if (AAGeneratorInitUtilities::CanExportProperty(pProperty))
		{
			m_exportInfo.AddDataMember(dataMemberInfo);
		}
	}
}

void FUClassAAGenerator::ExportFunctionMembersToMemory()
{
	for (TFieldIterator<UFunction> FuncIt(m_uclass, EFieldIteratorFlags::ExcludeSuper); FuncIt; ++FuncIt)
	{
		UFunction* Function = *FuncIt;
		if (CanExportFunction(Function))
		{
			AAGeneratorInitUtilities::FunctionMemberExportInfo funcMemberInfo =
				AAGeneratorInitUtilities::FunctionMemberExportInfo::Construct(m_uclass, Function);
			m_exportInfo.AddFunctionMember(funcMemberInfo);
		}
	}
}

bool FUClassAAGenerator::CanExportFunction(UFunction* function)
{
	if (!AAGeneratorInitUtilities::CanExportFunction(function))
	{
		return false;
	}

	if (function->HasAnyFunctionFlags(FUNC_Delegate | FUNC_Private | FUNC_Protected))
	{
		return false;
	}

	// if (FProperty* returnProperty = function->GetReturnProperty())
	// {
	// 	if (!returnProperty->IsA(FNumericProperty::StaticClass()) &&
	// 		!returnProperty->IsA(FEnumProperty::StaticClass()) &&
	// 		!returnProperty->IsA(FBoolProperty::StaticClass()) &&
	// 		!returnProperty->HasAnyPropertyFlags(CPF_ReferenceParm | CPF_InstancedReference))
	// 	{
	// 		return false;
	// 	}
	// }

	return function->HasAnyFunctionFlags(FUNC_BlueprintCallable | FUNC_BlueprintPure);
}
