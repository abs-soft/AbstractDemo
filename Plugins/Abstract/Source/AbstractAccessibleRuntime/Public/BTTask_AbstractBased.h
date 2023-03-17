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

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AI/UE_BTTask.h"
#include "AbstractBasedInterface.h"
#include "BTTask_AbstractBased.generated.h"

class AActor;
class AAIController;
class APawn;
class UBehaviorTree;

UCLASS()
class ABSTRACTACCESSIBLERUNTIME_API UBTTask_AbstractBased : public UBTTaskNode, public IAbstractBasedInterface
{
	GENERATED_UCLASS_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override {}
	virtual FString GetStaticDescription() const override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual void OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual void SetOwner(AActor* ActorOwner) override;

	UPROPERTY(EditAnywhere)
	FString AbstractClassDefinitionIdentifier;

protected:
	/** Cached AIController owner of BehaviorTreeComponent. */
	UPROPERTY(Transient)
	TObjectPtr<AAIController> AIOwner;
	// 
	// /** Cached actor owner of BehaviorTreeComponent. */
	// UPROPERTY(Transient)
	// TObjectPtr<AActor> ActorOwner;

	/** If any of the Tick functions is implemented, how often should they be ticked.
	 *	Values < 0 mean 'every tick'. */
	// UPROPERTY(EditAnywhere, Category = Task)
	// FIntervalCountdown TickInterval;

	// /** temporary variable for ReceiveExecute(Abort)-FinishExecute(Abort) chain */
	// mutable TEnumAsByte<EBTNodeResult::Type> CurrentCallResult;

	/** properties that should be copied */
	// TArray<FProperty*> PropertyData;

	/** show detailed information about properties */
	// UPROPERTY(EditInstanceOnly, Category=Description)
	// uint32 bShowPropertyDetails : 1;

	// /** set when task enters Aborting state */
	// uint32 bIsAborting : 1;

	// /** if set, execution is inside blueprint's ReceiveExecute(Abort) event
	//   * FinishExecute(Abort) function should store their result in CurrentCallResult variable */
	// mutable uint32 bStoreFinishResult : 1;

	// /** finishes task execution with Success or Fail result */
	// UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree")
	// void FinishExecute(bool bSuccess);
	// 
	// /** aborts task execution */
	// UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree")
	// void FinishAbort();

	// /** check if task is currently being executed */
	// UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree")
	// bool IsTaskExecuting() const;
	// 
	// /** check if task is currently being aborted */
	// UFUNCTION(BlueprintCallable, Category = "AI|BehaviorTree")
	// bool IsTaskAborting() const;

	/** ticks this task */
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	virtual AbstractSDK::AbsClass* GetInternal() override;

private:
	UE_BTTask m_internal;
};
