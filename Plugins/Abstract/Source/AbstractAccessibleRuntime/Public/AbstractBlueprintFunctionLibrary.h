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
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AbstractBlueprintFunctionLibrary.generated.h"

UCLASS()
class ABSTRACTACCESSIBLERUNTIME_API UAbstractBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure)
	static bool GetAbsClassVarBoolean(UObject* target, FString label);

	UFUNCTION(BlueprintPure)
	static int GetAbsClassVarInteger(UObject* target, FString label);

	UFUNCTION(BlueprintPure)
	static float GetAbsClassVarFloat(UObject* target, FString label);

	UFUNCTION(BlueprintPure)
	static double GetAbsClassVarDouble(UObject* target, FString label);

	UFUNCTION(BlueprintPure)
	static UClass* GetAbsClassVarUEClassType(UObject* target, FString label);

	UFUNCTION(BlueprintPure)
	static AActor* GetAbsClassVarActor(UObject* target, FString label);

	UFUNCTION(BlueprintCallable)
	static void SetAbsClassVarBoolean(UObject* target, FString label, bool value);

	UFUNCTION(BlueprintCallable)
	static void SetAbsClassVarInteger(UObject* target, FString label, int value);

	UFUNCTION(BlueprintCallable)
	static void SetAbsClassVarFloat(UObject* target, FString label, float value);

	UFUNCTION(BlueprintCallable)
	static void SetAbsClassVarDouble(UObject* target, FString label, double value);

	UFUNCTION(BlueprintCallable)
	static void SetAbsClassVarUEClassType(UObject* target, FString label, UClass* value);

	UFUNCTION(BlueprintCallable)
	static void SetAbsClassVarActor(UObject* target, FString label, AActor* value);
};
