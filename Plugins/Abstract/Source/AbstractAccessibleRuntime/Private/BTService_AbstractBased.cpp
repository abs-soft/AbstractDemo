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

#include "BTService_AbstractBased.h"
// #include "AIController.h"
// #include "BehaviorTree/BTFunctionLibrary.h"
// #include "BlueprintNodeHelpers.h"
// #include "BehaviorTree/BehaviorTree.h"
#include "AbstractLoader.h"

#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "BlueprintNodeHelpers.h"
#include "BehaviorTree/BehaviorTree.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
UBTService_AbstractBased::UBTService_AbstractBased(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	UClass* StopAtClass = UBTService_AbstractBased::StaticClass();
	// ReceiveTickImplementations = FBTNodeBPImplementationHelper::CheckEventImplementationVersion(TEXT("ReceiveTick"), TEXT("ReceiveTickAI"), *this, *StopAtClass);
	// ReceiveActivationImplementations = FBTNodeBPImplementationHelper::CheckEventImplementationVersion(TEXT("ReceiveActivation"), TEXT("ReceiveActivationAI"), *this, *StopAtClass);
	// ReceiveDeactivationImplementations = FBTNodeBPImplementationHelper::CheckEventImplementationVersion(TEXT("ReceiveDeactivation"), TEXT("ReceiveDeactivationAI"), *this, *StopAtClass);
	// ReceiveSearchStartImplementations = FBTNodeBPImplementationHelper::CheckEventImplementationVersion(TEXT("ReceiveSearchStart"), TEXT("ReceiveSearchStartAI"), *this, *StopAtClass);

	// bNotifyBecomeRelevant = ReceiveActivationImplementations != 0;
	// bNotifyCeaseRelevant = ReceiveDeactivationImplementations != 0;
	// bNotifyOnSearch = ReceiveSearchStartImplementations != 0;
	bNotifyTick = true; // ReceiveTickImplementations != 0;
	// bShowPropertyDetails = true;

	// all blueprint based nodes must create instances
	bCreateNodeInstance = true;

	// if (HasAnyFlags(RF_ClassDefaultObject))
	// {
	// 	BlueprintNodeHelpers::CollectPropertyData(this, StopAtClass, PropertyData);
	// }
}

void UBTService_AbstractBased::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (AbstractLoader::Loaded())
	{
		m_internal.LoadDefinition(AbstractLoader::GetLibrary(), TCHAR_TO_UTF8(*AbstractClassDefinitionIdentifier));
	}

	// if (Asset.BlackboardAsset)
	// {
	// 	BlueprintNodeHelpers::ResolveBlackboardSelectors(*this, *StaticClass(), *Asset.BlackboardAsset);
	// }
}

AbstractSDK::AbsClass* UBTService_AbstractBased::GetInternal()
{
	return &m_internal;
}

void UBTService_AbstractBased::SetOwner(AActor* InActorOwner)
{
	ActorOwner = InActorOwner;
	AIOwner = Cast<AAIController>(InActorOwner);
}

void UBTService_AbstractBased::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	// // check flag, it could be used because user wants tick
	// if (AIOwner != nullptr && (ReceiveActivationImplementations & FBTNodeBPImplementationHelper::AISpecific))
	// {
	// 	ReceiveActivationAI(AIOwner, AIOwner->GetPawn());
	// }
	// else if (ReceiveActivationImplementations & FBTNodeBPImplementationHelper::Generic)
	// {
	// 	ReceiveActivation(ActorOwner);
	// }
}

void UBTService_AbstractBased::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);

	// if (!OwnerComp.HasAnyFlags(RF_BeginDestroyed) && OwnerComp.GetOwner())
	// {
	// 	// force dropping all pending latent actions associated with this blueprint
	// 	// we can't have those resuming activity when node is/was aborted
	// 	BlueprintNodeHelpers::AbortLatentActions(OwnerComp, *this);

	// 	if (AIOwner != nullptr && (ReceiveDeactivationImplementations & FBTNodeBPImplementationHelper::AISpecific))
	// 	{
	// 		ReceiveDeactivationAI(AIOwner, AIOwner->GetPawn());
	// 	}
	// 	else if (ReceiveDeactivationImplementations & FBTNodeBPImplementationHelper::Generic)
	// 	{
	// 		ReceiveDeactivation(ActorOwner);
	// 	}
	// }
	// else
	// {
	// 	UE_LOG(LogBehaviorTree, Warning,
	// 		TEXT("OnCeaseRelevant called on Blueprint service %s with invalid owner.  OwnerComponent: %s, OwnerComponent Owner: %s.  %s")
	// 		, *GetNameSafe(this), *OwnerComp.GetName(), *GetNameSafe(OwnerComp.GetOwner())
	// 		, OwnerComp.HasAnyFlags(RF_BeginDestroyed) ? TEXT("OwnerComponent has BeginDestroyed flag") : TEXT("")
	// 	);
	// }
}

void UBTService_AbstractBased::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);

	// if (ReceiveSearchStartImplementations != 0)
	// {
	// 	if (AIOwner != nullptr && (ReceiveSearchStartImplementations & FBTNodeBPImplementationHelper::AISpecific))
	// 	{
	// 		ReceiveSearchStartAI(AIOwner, AIOwner->GetPawn());
	// 	}
	// 	else if (ReceiveSearchStartImplementations & FBTNodeBPImplementationHelper::Generic)
	// 	{
	// 		ReceiveSearchStart(ActorOwner);
	// 	}
	// }
}

void UBTService_AbstractBased::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	m_internal.ReceiveTick(this, AIOwner, AIOwner->GetPawn(), DeltaSeconds);

	// if (AIOwner != nullptr && (ReceiveTickImplementations & FBTNodeBPImplementationHelper::AISpecific))
	// {
	// 	ReceiveTickAI(AIOwner, AIOwner->GetPawn(), DeltaSeconds);
	// }
	// else if (ReceiveTickImplementations & FBTNodeBPImplementationHelper::Generic)
	// {
	// 	ReceiveTick(ActorOwner, DeltaSeconds);
	// }
}

// bool UBTService_BlueprintBase::IsServiceActive() const
// {
// 	UBehaviorTreeComponent* OwnerComp = Cast<UBehaviorTreeComponent>(GetOuter());
// 	const bool bIsActive = OwnerComp->IsAuxNodeActive(this);
// 	return bIsActive;
// }

FString UBTService_AbstractBased::GetStaticServiceDescription() const
{
// 	FString ReturnDesc
// #if WITH_EDITORONLY_DATA
// 		= CustomDescription
// #endif // WITH_EDITORONLY_DATA
// 		;

// 	UBTService_BlueprintBase* CDO = (UBTService_BlueprintBase*)(GetClass()->GetDefaultObject());
// 	if (CDO)
// 	{
// 		if (bShowEventDetails)
// 		{
// 			ReturnDesc += FString::Printf(TEXT("%s, %s, %s, %s\n"),
// 				ReceiveTickImplementations != 0 ? *GetStaticTickIntervalDescription() : TEXT("No tick"),
// 				ReceiveActivationImplementations != 0 ? TEXT("Activation") : TEXT("No Activation"),
// 				ReceiveDeactivationImplementations != 0 ? TEXT("Deactivation") : TEXT("No Deactivation"),
// 				ReceiveSearchStartImplementations != 0 ? TEXT("Search Start") : TEXT("No Search Start"));
// 		}
// 		else
// 		{
// 			// Only show the description text ("tick every 0.40s..0.60s") if we actually have a Tick implementation
// 			if (ReceiveTickImplementations != 0)
// 			{
// 				ReturnDesc += Super::GetStaticServiceDescription();
// 			}
// 			ReturnDesc += TEXT('\n');
// 		}

// 		if (bShowPropertyDetails)
// 		{
// 			UClass* StopAtClass = UBTService_BlueprintBase::StaticClass();
// 			FString PropertyDesc = BlueprintNodeHelpers::CollectPropertyDescription(this, StopAtClass, CDO->PropertyData);
// 			if (PropertyDesc.Len())
// 			{
// 				ReturnDesc += TEXT("\n");
// 				ReturnDesc += PropertyDesc;
// 			}
// 		}
// 	}

// 	return ReturnDesc;

	return TEXT("ABS SERVICE");
}

void UBTService_AbstractBased::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	// UBTService_BlueprintBase* CDO = (UBTService_BlueprintBase*)(GetClass()->GetDefaultObject());
	// if (CDO && CDO->PropertyData.Num())
	// {
	// 	UClass* StopAtClass = UBTService_BlueprintBase::StaticClass();
	// 	BlueprintNodeHelpers::DescribeRuntimeValues(this, CDO->PropertyData, Values);
	// }
}

void UBTService_AbstractBased::OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp)
{
	// force dropping all pending latent actions associated with this blueprint
	// BlueprintNodeHelpers::AbortLatentActions(OwnerComp, *this);
}
