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
#include "Components/ActorComponent.h"
#include "Actor/UE_ActorComponent.h"
#include "AbstractBasedInterface.h"
#include "ActorComponent_AbstractBased.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABSTRACTACCESSIBLERUNTIME_API UActorComponent_AbstractBased : public UActorComponent, public IAbstractBasedInterface
{
	GENERATED_BODY()

public:
	UActorComponent_AbstractBased();

	UPROPERTY(EditAnywhere)
	FString AbstractClassDefinitionIdentifier;

	UFUNCTION(BlueprintCallable)
	void InvokeOnBeginOverlap(AActor* otherActor);

	UFUNCTION(BlueprintCallable)
	void InvokeOnEndOverlap(AActor* otherActor);

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual AbstractSDK::AbsClass* GetInternal() override;

private:
	UE_ActorComponent m_internal;
};
