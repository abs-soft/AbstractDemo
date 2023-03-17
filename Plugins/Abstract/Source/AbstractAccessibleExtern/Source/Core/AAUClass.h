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

#include <AbstractSDK.h>

#include "AAFString.h"

class UObject;
ABSTRACT_SDK_VALUE_TYPE_DECLARE(AAUObject, UObject*);

class AActor;
ABSTRACT_SDK_VALUE_TYPE_DECLARE(AAAActor, AActor*);

class UClass;
ABSTRACT_SDK_VALUE_TYPE_DEFINITION_EXTERN(
	ABS_SDK_PROPERTIES(DisplayText = "UE Class Type", ScriptName = "UEClass", Priority = "high"),
	AAUClass,
	UClass*);

ABSTRACT_SDK_NODE_DEFINITION_EXTERN_DECLARE(
    ABS_SDK_PROPERTIES(
        Type="Evaluation",
        NodeDisplayText="Get UE Class Type",
        ScriptName="GetUEClass",
        Category="UE Type",
        Keywords="class type",
        ToolTips="Gets the UE Class Type of the source object.",
        Priority = "high"),
    GetUEClassType,
    AAUClass,
    ABS_SDK_PARAM(AAUObject, Source));

ABSTRACT_SDK_NODE_DEFINITION_EXTERN_DECLARE(
    ABS_SDK_PROPERTIES(
        Type = "Execution",
        NodeDisplayText = "Spawn Actor from UE Class Type",
        ScriptName = "SpawnActorFromUEClassType",
        Category = "UE Type",
        Keywords = "actor class type",
        ToolTips = "Spawns an actor of the specified UE Class Type.",
        Priority = "high"),
    SpawnActorFromUEClassType,
    AAAActor,
    ABS_SDK_PARAM(AAUObject, WorldContextObject),
    ABS_SDK_PARAM(AAUClass, ActorType),
    ABS_SDK_PARAM(__CREF__AAFVector, Location));
