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

#include "BTTask_AbstractBased.h"
#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "BlueprintNodeHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AbstractLoader.h"

UBTTask_AbstractBased::UBTTask_AbstractBased(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	const UClass* StopAtClass = UBTTask_AbstractBased::StaticClass();
	// ReceiveTickImplementations = FBTNodeBPImplementationHelper::CheckEventImplementationVersion(TEXT("ReceiveTick"), TEXT("ReceiveTickAI"), *this, *StopAtClass);
	// ReceiveExecuteImplementations = FBTNodeBPImplementationHelper::CheckEventImplementationVersion(TEXT("ReceiveExecute"), TEXT("ReceiveExecuteAI"), *this, *StopAtClass);
	// ReceiveAbortImplementations = FBTNodeBPImplementationHelper::CheckEventImplementationVersion(TEXT("ReceiveAbort"), TEXT("ReceiveAbortAI"), *this, *StopAtClass);

	INIT_TASK_NODE_NOTIFY_FLAGS();
	bNotifyTick = true; // ReceiveTickImplementations != FBTNodeBPImplementationHelper::NoImplementation;
	// bShowPropertyDetails = true;
	// bIsAborting = false;

	// all blueprint based nodes must create instances
	bCreateNodeInstance = true;

	// if (HasAnyFlags(RF_ClassDefaultObject))
	// {
	// 	BlueprintNodeHelpers::CollectPropertyData(this, StopAtClass, PropertyData);
	// }
}

void UBTTask_AbstractBased::InitializeFromAsset(UBehaviorTree& Asset)
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

AbstractSDK::AbsClass* UBTTask_AbstractBased::GetInternal()
{
	return &m_internal;
}

void UBTTask_AbstractBased::SetOwner(AActor* InActorOwner) 
{ 
	// ActorOwner = InActorOwner;
	AIOwner = Cast<AAIController>(InActorOwner);
}

EBTNodeResult::Type UBTTask_AbstractBased::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto result = static_cast<EBTNodeResult::Type>(m_internal.ReceiveExecute(this, AIOwner, AIOwner->GetPawn()));
	return result;
	// fail when task doesn't react to execution (start or tick)
	// CurrentCallResult = (ReceiveExecuteImplementations != 0 || ReceiveTickImplementations != 0) ? EBTNodeResult::InProgress : EBTNodeResult::Failed;
	// bIsAborting = false;

	// if (ReceiveExecuteImplementations != FBTNodeBPImplementationHelper::NoImplementation)
	// {
	// 	bStoreFinishResult = true;
	// 
	// 	if (AIOwner != nullptr && (ReceiveExecuteImplementations & FBTNodeBPImplementationHelper::AISpecific))
	// 	{
	// 		ReceiveExecuteAI(AIOwner, AIOwner->GetPawn());
	// 	}
	// 	else if (ReceiveExecuteImplementations & FBTNodeBPImplementationHelper::Generic)
	// 	{
	// 		ReceiveExecute(ActorOwner);
	// 	}
	// 
	// 	bStoreFinishResult = false;
	// }
}

EBTNodeResult::Type UBTTask_AbstractBased::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// force dropping all pending latent actions associated with this blueprint
	// we can't have those resuming activity when node is/was aborted
	// BlueprintNodeHelpers::AbortLatentActions(OwnerComp, *this);

	// CurrentCallResult = ReceiveAbortImplementations != 0 ? EBTNodeResult::InProgress : EBTNodeResult::Aborted;
	// bIsAborting = true;

	// if (ReceiveAbortImplementations != FBTNodeBPImplementationHelper::NoImplementation)
	// {
	// 	bStoreFinishResult = true;
	// 
	// 	if (AIOwner != nullptr && (ReceiveAbortImplementations & FBTNodeBPImplementationHelper::AISpecific))
	// 	{
	// 		ReceiveAbortAI(AIOwner, AIOwner->GetPawn());
	// 	}
	// 	else if (ReceiveAbortImplementations & FBTNodeBPImplementationHelper::Generic)
	// 	{
	// 		ReceiveAbort(ActorOwner);
	// 	}
	// 
	// 	bStoreFinishResult = false;
	// }

	if (GEngine != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Black, TEXT("ABORT"), true);
	}

	return EBTNodeResult::InProgress;
}

void UBTTask_AbstractBased::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto tickResult = static_cast<EBTNodeResult::Type>(m_internal.ReceiveTick(this, AIOwner, AIOwner->GetPawn(), DeltaSeconds));
	if (tickResult != EBTNodeResult::InProgress)
	{
		FinishLatentTask(OwnerComp, tickResult);
	}

	// if (TickInterval.Tick(DeltaSeconds))
	// {
	// 	DeltaSeconds = TickInterval.GetElapsedTimeWithFallback(DeltaSeconds);
	// 
	// 	// if (AIOwner != nullptr && (ReceiveTickImplementations & FBTNodeBPImplementationHelper::AISpecific))
	// 	// {
	// 	// 	ReceiveTickAI(AIOwner, AIOwner->GetPawn(), DeltaSeconds);
	// 	// }
	// 	// else if (ReceiveTickImplementations & FBTNodeBPImplementationHelper::Generic)
	// 	// {
	// 	// 	ReceiveTick(ActorOwner, DeltaSeconds);
	// 	// }
	// 
	// 	TickInterval.Reset();
	// }
}

void UBTTask_AbstractBased::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	// TickInterval.Set(0); // so that we tick as soon as enabled back

	// if (TaskResult != EBTNodeResult::InProgress)
	// {
	// 	BlueprintNodeHelpers::AbortLatentActions(OwnerComp, *this);
	// }
}

// void UBTTask_AbstractBased::FinishExecute(bool bSuccess)
// {
// 	UBehaviorTreeComponent* OwnerComp = Cast<UBehaviorTreeComponent>(GetOuter());
// 	const EBTNodeResult::Type NodeResult(bSuccess ? EBTNodeResult::Succeeded : EBTNodeResult::Failed);
// 
// 	if (bStoreFinishResult)
// 	{
// 		CurrentCallResult = NodeResult;
// 	}
// 	else if (OwnerComp && !bIsAborting)
// 	{
// 		FinishLatentTask(*OwnerComp, NodeResult);
// 	}
// }
// 
// void UBTTask_AbstractBased::FinishAbort()
// {
// 	UBehaviorTreeComponent* OwnerComp = Cast<UBehaviorTreeComponent>(GetOuter());
// 
// 	if (bStoreFinishResult)
// 	{
// 		constexpr EBTNodeResult::Type NodeResult(EBTNodeResult::Aborted);
// 		CurrentCallResult = NodeResult;
// 	}
// 	else if (OwnerComp && bIsAborting)
// 	{
// 		FinishLatentAbort(*OwnerComp);
// 	}
// }

// bool UBTTask_AbstractBased::IsTaskExecuting() const
// {
// 	const UBehaviorTreeComponent* OwnerComp = Cast<UBehaviorTreeComponent>(GetOuter());
// 	const EBTTaskStatus::Type TaskStatus = OwnerComp->GetTaskStatus(this);
// 
// 	return (TaskStatus == EBTTaskStatus::Active);
// }
// 
// bool UBTTask_AbstractBased::IsTaskAborting() const
// {
// 	// use already cached data
// 	return bIsAborting;
// }

FString UBTTask_AbstractBased::GetStaticDescription() const
{
// 	FString ReturnDesc =
// #if WITH_EDITORONLY_DATA
// 		CustomDescription.Len() ? CustomDescription :
// #endif // WITH_EDITORONLY_DATA
// 		Super::GetStaticDescription();
// 
// 	UBTTask_AbstractBased* CDO = static_cast<UBTTask_AbstractBased*>(GetClass()->GetDefaultObject());
// 	if (bShowPropertyDetails && CDO)
// 	{
// 		const UClass* StopAtClass = UBTTask_AbstractBased::StaticClass();
// 		FString PropertyDesc = BlueprintNodeHelpers::CollectPropertyDescription(this, StopAtClass, CDO->PropertyData);
// 		if (PropertyDesc.Len())
// 		{
// 			ReturnDesc += TEXT(":\n\n");
// 			ReturnDesc += PropertyDesc;
// 		}
// 	}
// 
// 	return ReturnDesc;
	return TEXT("ABS TASK");
}

void UBTTask_AbstractBased::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	// UBTTask_AbstractBased* CDO = static_cast<UBTTask_AbstractBased*>(GetClass()->GetDefaultObject());
	// if (CDO && CDO->PropertyData.Num())
	// {
	// 	BlueprintNodeHelpers::DescribeRuntimeValues(this, CDO->PropertyData, Values);
	// }
}

void UBTTask_AbstractBased::OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp)
{
	// force dropping all pending latent actions associated with this blueprint
	// BlueprintNodeHelpers::AbortLatentActions(OwnerComp, *this);
}

