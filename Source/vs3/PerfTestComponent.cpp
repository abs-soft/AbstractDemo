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

#include "PerfTestComponent.h"

UPerfTestComponent::UPerfTestComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPerfTestComponent::BeginPlay()
{
	Super::BeginPlay();

	m_velocity = { 0.0f, 0.0f, 1.0f };
}

void UPerfTestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const int CPULoadMultiplier = 10000;
	for (int i = 0; i < CPULoadMultiplier; ++i)
	{
		AActor* owner = GetOwner();
		const FVector ownerLocation = owner->GetActorLocation();
		const FVector acceleration = -ownerLocation.GetSafeNormal(0.0001f) / ownerLocation.Length();
		m_velocity = m_velocity + acceleration * 0.016f * 1.0f;
		owner->SetActorLocation(ownerLocation + m_velocity * 0.0016f * 1.0f);
	}
}
