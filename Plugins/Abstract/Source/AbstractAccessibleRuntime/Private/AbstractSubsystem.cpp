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

#include "AbstractSubsystem.h"

#include "Materials/Material.h"
#include "Misc/FileHelper.h"
#include "AbstractLoader.h"
#include "../Generated/AllInclude.inl"
#include "../CustomExterns/AllIncludeCustomExterns.inl"

namespace
{
    bool initializedExterns = false;
    void InitializeExterns()
    {
        if (!initializedExterns)
        {
            AbstractRuntimeGenerated::InitAll();
            AbstractRuntimeCustomExterns::InitAll();

            initializedExterns = true;
        }
    }
}

bool UAbstractSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    return true;
}

void UAbstractSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    FString ProjectFilePath = FPaths::GetProjectFilePath();
    FString ProjectPath = FPaths::GetPath(ProjectFilePath);
    FString ConfigFilePath = ProjectPath / FString("Config/AbstractAccessible/RuntimeConfig.ini");

    FString abexFilepath;
    GConfig->GetString(TEXT("Profile"), TEXT("AbexFilepath"), abexFilepath, ConfigFilePath);
    AbstractLoader::Load(ProjectPath / abexFilepath);

    InitializeExterns();

    UObject* testO = nullptr;
    AActor* test = Cast<AActor>(testO);
}

void UAbstractSubsystem::Deinitialize()
{
    AbstractLoader::Unload();
}
