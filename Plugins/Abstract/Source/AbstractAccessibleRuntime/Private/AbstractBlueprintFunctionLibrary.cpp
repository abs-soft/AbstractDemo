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

#include "AbstractBlueprintFunctionLibrary.h"

#include "AbstractBasedInterface.h"
#include "ActorComponent_AbstractBased.h"

bool UAbstractBlueprintFunctionLibrary::GetAbsClassVarBoolean(UObject* target, FString label)
{
    bool result = {};
    if (IAbstractBasedInterface* abstractBasedObject = Cast<IAbstractBasedInterface>(target))
    {
        abstractBasedObject->GetInternal()->GetClassVar<bool>(TCHAR_TO_UTF8(*label), result);
    }

    return result;
}

int UAbstractBlueprintFunctionLibrary::GetAbsClassVarInteger(UObject* target, FString label)
{
    int result = {};
    if (IAbstractBasedInterface* abstractBasedObject = Cast<IAbstractBasedInterface>(target))
    {
        abstractBasedObject->GetInternal()->GetClassVar<int>(TCHAR_TO_UTF8(*label), result);
    }

    return result;
}

float UAbstractBlueprintFunctionLibrary::GetAbsClassVarFloat(UObject* target, FString label)
{
    float result = {};
    if (IAbstractBasedInterface* abstractBasedObject = Cast<IAbstractBasedInterface>(target))
    {
        abstractBasedObject->GetInternal()->GetClassVar<float>(TCHAR_TO_UTF8(*label), result);
    }

    return result;
}

double UAbstractBlueprintFunctionLibrary::GetAbsClassVarDouble(UObject* target, FString label)
{
    double result = {};
    if (IAbstractBasedInterface* abstractBasedObject = Cast<IAbstractBasedInterface>(target))
    {
        abstractBasedObject->GetInternal()->GetClassVar<double>(TCHAR_TO_UTF8(*label), result);
    }

    return result;
}

UClass* UAbstractBlueprintFunctionLibrary::GetAbsClassVarUEClassType(UObject* target, FString label)
{
    UClass* result = {};
    if (IAbstractBasedInterface* abstractBasedObject = Cast<IAbstractBasedInterface>(target))
    {
        abstractBasedObject->GetInternal()->GetClassVar<UClass*>(TCHAR_TO_UTF8(*label), result);
    }

    return result;
}

AActor* UAbstractBlueprintFunctionLibrary::GetAbsClassVarActor(UObject* target, FString label)
{
    AActor* result = {};
    if (IAbstractBasedInterface* abstractBasedObject = Cast<IAbstractBasedInterface>(target))
    {
        abstractBasedObject->GetInternal()->GetClassVar<AActor*>(TCHAR_TO_UTF8(*label), result);
    }

    return result;
}

void UAbstractBlueprintFunctionLibrary::SetAbsClassVarBoolean(UObject* target, FString label, bool value)
{
    if (IAbstractBasedInterface* abstractBasedObject = Cast<IAbstractBasedInterface>(target))
    {
        abstractBasedObject->GetInternal()->SetClassVar<bool>(TCHAR_TO_UTF8(*label), value);
    }
}

void UAbstractBlueprintFunctionLibrary::SetAbsClassVarInteger(UObject* target, FString label, int value)
{
    if (IAbstractBasedInterface* abstractBasedObject = Cast<IAbstractBasedInterface>(target))
    {
        abstractBasedObject->GetInternal()->SetClassVar<int>(TCHAR_TO_UTF8(*label), value);
    }
}

void UAbstractBlueprintFunctionLibrary::SetAbsClassVarFloat(UObject* target, FString label, float value)
{
    if (IAbstractBasedInterface* abstractBasedObject = Cast<IAbstractBasedInterface>(target))
    {
        abstractBasedObject->GetInternal()->SetClassVar<float>(TCHAR_TO_UTF8(*label), value);
    }
}

void UAbstractBlueprintFunctionLibrary::SetAbsClassVarDouble(UObject* target, FString label, double value)
{
    if (IAbstractBasedInterface* abstractBasedObject = Cast<IAbstractBasedInterface>(target))
    {
        abstractBasedObject->GetInternal()->SetClassVar<double>(TCHAR_TO_UTF8(*label), value);
    }
}

void UAbstractBlueprintFunctionLibrary::SetAbsClassVarUEClassType(UObject* target, FString label, UClass* value)
{
    if (IAbstractBasedInterface* abstractBasedObject = Cast<IAbstractBasedInterface>(target))
    {
        abstractBasedObject->GetInternal()->SetClassVar<UClass*>(TCHAR_TO_UTF8(*label), value);
    }
}

void UAbstractBlueprintFunctionLibrary::SetAbsClassVarActor(UObject* target, FString label, AActor* value)
{
    if (IAbstractBasedInterface* abstractBasedObject = Cast<IAbstractBasedInterface>(target))
    {
        abstractBasedObject->GetInternal()->SetClassVar<AActor*>(TCHAR_TO_UTF8(*label), value);
    }
}

UActorComponent* UAbstractBlueprintFunctionLibrary::GetComponentByTag(AActor* target, FName tag)
{
    TArray<UActorComponent*> abstractComponents = target->GetComponentsByTag(UActorComponent::StaticClass(), tag);
    if (abstractComponents.Num() > 0)
    {
        return abstractComponents[0];
    }
    else
    {
        return nullptr;
    }
}

UActorComponent_AbstractBased* UAbstractBlueprintFunctionLibrary::GetAbstractComponentByTag(AActor* target, FName tag)
{
    TArray<UActorComponent*> abstractComponents = target->GetComponentsByTag(UActorComponent_AbstractBased::StaticClass(), tag);
    if (abstractComponents.Num() > 0)
    {
        return Cast<UActorComponent_AbstractBased>(abstractComponents[0]);
    }
    else
    {
        return nullptr;
    }
}

void UAbstractBlueprintFunctionLibrary::ActivateAllAbstractComponentsWithTag(AActor* target, FName tag)
{
    TArray<UActorComponent*> abstractComponents = target->GetComponentsByTag(UActorComponent_AbstractBased::StaticClass(), tag);
    for (UActorComponent* it : abstractComponents)
    {
        it->SetComponentTickEnabled(true);
    }
}

void UAbstractBlueprintFunctionLibrary::DeactivateAllAbstractComponentsWithTag(AActor* target, FName tag)
{
    TArray<UActorComponent*> abstractComponents = target->GetComponentsByTag(UActorComponent_AbstractBased::StaticClass(), tag);
    for (UActorComponent* it : abstractComponents)
    {
        it->SetComponentTickEnabled(false);
    }
}
