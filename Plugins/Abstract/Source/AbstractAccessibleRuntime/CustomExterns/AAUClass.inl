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

namespace
{
	AAUClass GetUEClassTypeIMPLEMENTATION(AAUObject Source)
	{
		if (Source)
		{
			return Source->GetClass();
		}

		return nullptr;
	}

	AAUClass GetInvalidUEClassTypeIMPLEMENTATION()
	{
		return nullptr;
	}

	AAAActor SpawnActorFromUEClassTypeIMPLEMENTATION(AAUObject WorldContextObject, AAUClass ActorType, __CREF__AAFVector Location)
	{
		if (GEngine != nullptr)
		{
			if (UWorld* world = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
			{
				FActorSpawnParameters spawnInfo;
				spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				spawnInfo.bNoFail = true;
				spawnInfo.ObjectFlags = RF_Transient;
				AActor* result = world->SpawnActor(ActorType, nullptr, nullptr, spawnInfo);
				if (result != nullptr)
				{
					result->SetActorLocation(Location.GetConst<FVector>());
					return result;
				}
			}
		}

		return nullptr;
	}
}

namespace AbstractRuntimeCustomExterns
{
	void InitExterns_UClass()
	{
		ABSTRACT_SDK_NODE_DEFINITION_EXTERN_DEFINE(
			GetUEClassType,
			GetUEClassTypeIMPLEMENTATION,
			AAUClass,
			ABS_SDK_PARAM(AAUObject, Source));
		ABSTRACT_SDK_NODE_DEFINITION_EXTERN_DEFINE(
			GetInvalidUEClassType,
			GetInvalidUEClassTypeIMPLEMENTATION,
			AAUClass);
		ABSTRACT_SDK_NODE_DEFINITION_EXTERN_DEFINE(
			SpawnActorFromUEClassType,
			SpawnActorFromUEClassTypeIMPLEMENTATION,
			AAAActor,
			ABS_SDK_PARAM(AAUObject, WorldContextObject),
			ABS_SDK_PARAM(AAUClass, ActorType),
			ABS_SDK_PARAM(__CREF__AAFVector, Location));
	}
}
