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

#include "AbstractAccessibleConfigManager.h"
#include "AAGeneratorManager.h"

// DECLARE_LOG_CATEGORY_EXTERN(LogLuaGenerator, Log, All);

#define SafeDelete(pItem) if (pItem) { delete pItem; }
#define EndLinePrintf(FormatString, ...) FString::Printf(TEXT("%s\r\n"), *FString::Printf(FormatString, ##__VA_ARGS__ ))
#define GeneratorLog(LogVerbosity, FormatString, ...) UE_LOG(LogLuaGenerator, LogVerbosity, FormatString, ##__VA_ARGS__ )


#if 1
#define DebugLog(FormatString, ...) UE_LOG(LogLuaGenerator, Error, FormatString, ##__VA_ARGS__ )
#else
#define DebugLog(FormatString, ...)
#endif

#if 0
#define DebugProcedure(FormatString, ...) UE_LOG(LogLuaGenerator, Error, FormatString, ##__VA_ARGS__ )
#else
#define DebugProcedure(FormatString, ...)
#endif

class FAbstractAccessibleGeneratorGlobal
{
public:
    static FAbstractAccessibleConfigManager& GetConfig();
    static FAAGeneratorManager& GetGeneratorManager();
};
