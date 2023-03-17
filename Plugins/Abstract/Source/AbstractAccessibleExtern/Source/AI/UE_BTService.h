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

#include "UEAllHeader.h"

ABSTRACT_SDK_CLASS_DECLARATION(UE_BTService)
{
public:
    ABSTRACT_SDK_CLASS_LABEL("Behavior Tree Service");

    void LoadDefinition(const AbstractSDK::AbsLibrary& sourceLib, AbstractSDK::AbsStringParam definitionName);

    ABSTRACT_SDK_EVENT_DECLARATION("Receive Execute" /*, defaultReturnValue = "UEEBTNodeResult_Type.Succeeded"*/)
    AAEBTNodeResultType ReceiveExecute(AAUBTNode OwnerNode, AAAAIController OwnerController, AAAPawn ControlledPawn);

    ABSTRACT_SDK_EVENT_DECLARATION("Receive Tick" /*, defaultReturnValue = "UEEBTNodeResult_Type.InProgress"*/)
    AAEBTNodeResultType ReceiveTick(AAUBTNode OwnerNode, AAAAIController OwnerController, AAAPawn ControlledPawn, AABFloat DeltaSeconds);
};
