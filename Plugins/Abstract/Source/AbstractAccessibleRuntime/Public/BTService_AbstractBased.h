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
#include "BehaviorTree/BTService.h"
#include "AI/UE_BTTask.h"
#include "AI/UE_BTService.h"
#include "AbstractBasedInterface.h"
#include "BTService_AbstractBased.generated.h"

class AActor;
class AAIController;
class APawn;
class UBehaviorTree;

UCLASS()
class ABSTRACTACCESSIBLERUNTIME_API UBTService_AbstractBased : public UBTService, public IAbstractBasedInterface
{
	GENERATED_UCLASS_BODY()

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override {}
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override {}
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual void OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp) override;
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual void SetOwner(AActor* ActorOwner) override;

	UPROPERTY(EditAnywhere)
	FString AbstractClassDefinitionIdentifier;

protected:
	/** Cached AIController owner of BehaviorTreeComponent. */
	UPROPERTY(Transient)
	TObjectPtr<AAIController> AIOwner;

	/** Cached actor owner of BehaviorTreeComponent. */
	UPROPERTY(Transient)
	TObjectPtr<AActor> ActorOwner;

	// Gets the description for our service
	virtual FString GetStaticServiceDescription() const override;

	/** properties with runtime values, stored only in class default object */
	// TArray<FProperty*> PropertyData;

// #if WITH_EDITORONLY_DATA
// 	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Description)
// 	FString CustomDescription;
// #endif // WITH_EDITORONLY_DATA

	// /** show detailed information about properties */
	// UPROPERTY(EditInstanceOnly, Category=Description)
	// uint32 bShowPropertyDetails : 1;

	// /** show detailed information about implemented events */
	// UPROPERTY(EditInstanceOnly, Category = Description)
	// uint32 bShowEventDetails : 1;

	// /** set if ReceiveTick is implemented by blueprint */
	// uint32 ReceiveTickImplementations : 2;

	// /** set if ReceiveActivation is implemented by blueprint */
	// uint32 ReceiveActivationImplementations : 2;

	// /** set if ReceiveDeactivation is implemented by blueprint */
	// uint32 ReceiveDeactivationImplementations : 2;

	// /** set if ReceiveSearchStart is implemented by blueprint */
	// uint32 ReceiveSearchStartImplementations : 2;

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;

	/** tick function
	 *	@Note that if both generic and AI event versions are implemented only the more
	 *	suitable one will be called, meaning the AI version if called for AI, generic one otherwise */
	// UFUNCTION(BlueprintImplementableEvent)
	// void ReceiveTick(AActor* OwnerActor, float DeltaSeconds);

	/** task search enters branch of tree
	 *	@Note that if both generic and AI event versions are implemented only the more
	 *	suitable one will be called, meaning the AI version if called for AI, generic one otherwise */
	// UFUNCTION(BlueprintImplementableEvent)
	// void ReceiveSearchStart(AActor* OwnerActor);

	/** service became active
	 *	@Note that if both generic and AI event versions are implemented only the more
	 *	suitable one will be called, meaning the AI version if called for AI, generic one otherwise */
	// UFUNCTION(BlueprintImplementableEvent)
	// void ReceiveActivation(AActor* OwnerActor);

	/** service became inactive
	 *	@Note that if both generic and AI event versions are implemented only the more
	 *	suitable one will be called, meaning the AI version if called for AI, generic one otherwise */
	// UFUNCTION(BlueprintImplementableEvent)
	// void ReceiveDeactivation(AActor* OwnerActor);

	/** Alternative AI version of ReceiveTick function.
	 *	@see ReceiveTick for more details
	 *	@Note that if both generic and AI event versions are implemented only the more
	 *	suitable one will be called, meaning the AI version if called for AI, generic one otherwise */
	// UFUNCTION(BlueprintImplementableEvent, Category = AI)
	// void ReceiveTickAI(AAIController* OwnerController, APawn* ControlledPawn, float DeltaSeconds);

	/** Alternative AI version of ReceiveSearchStart function.
	 *	@see ReceiveSearchStart for more details
	 *	@Note that if both generic and AI event versions are implemented only the more
	 *	suitable one will be called, meaning the AI version if called for AI, generic one otherwise */
	// UFUNCTION(BlueprintImplementableEvent, Category = AI)
	// void ReceiveSearchStartAI(AAIController* OwnerController, APawn* ControlledPawn);

	/** Alternative AI version of ReceiveActivation function.
	 *	@see ReceiveActivation for more details
	 *	@Note that if both generic and AI event versions are implemented only the more
	 *	suitable one will be called, meaning the AI version if called for AI, generic one otherwise */
	// UFUNCTION(BlueprintImplementableEvent, Category = AI)
	// void ReceiveActivationAI(AAIController* OwnerController, APawn* ControlledPawn);

	/** Alternative AI version of ReceiveDeactivation function.
	 *	@see ReceiveDeactivation for more details
	 *	@Note that if both generic and AI event versions are implemented only the more
	 *	suitable one will be called, meaning the AI version if called for AI, generic one otherwise */
	// UFUNCTION(BlueprintImplementableEvent, Category = AI)
	// void ReceiveDeactivationAI(AAIController* OwnerController, APawn* ControlledPawn);

	// /** check if service is currently being active */
	// UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree")
	// bool IsServiceActive() const;

public:
	virtual AbstractSDK::AbsClass* GetInternal() override;

private:
	UE_BTService m_internal;
};
