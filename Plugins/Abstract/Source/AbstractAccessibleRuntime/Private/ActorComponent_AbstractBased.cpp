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

#include "ActorComponent_AbstractBased.h"
#include "AbstractLoader.h"

UActorComponent_AbstractBased::UActorComponent_AbstractBased()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UActorComponent_AbstractBased::InvokeOnBeginOverlap(AActor* otherActor)
{
	m_internal.OnBeginOverlap(this, GetOwner(), otherActor);
}

void UActorComponent_AbstractBased::InvokeOnEndOverlap(AActor* otherActor)
{
	m_internal.OnEndOverlap(this, GetOwner(), otherActor);
}

AbstractSDK::AbsClass* UActorComponent_AbstractBased::GetInternal()
{
	return &m_internal;
}

void UActorComponent_AbstractBased::BeginPlay()
{
	Super::BeginPlay();

	if (AbstractLoader::Loaded())
	{
		m_internal.LoadDefinition(AbstractLoader::GetLibrary(), TCHAR_TO_UTF8(*AbstractClassDefinitionIdentifier));
	}

	m_internal.BeginPlay(this, GetOwner());
}

void UActorComponent_AbstractBased::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	m_internal.Tick(this, GetOwner(), DeltaTime);
}
