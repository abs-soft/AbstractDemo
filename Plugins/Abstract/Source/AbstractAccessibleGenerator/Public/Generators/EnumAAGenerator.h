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

#include "IAAGenerator.h"
#include "AAGeneratorInitUtilities.h"

class FEnumAAGenerator : public IAAGenerator
{
public:
	static FString GetExportableName(UEnum* enumData);

	FEnumAAGenerator(UEnum* enumData);
	virtual ~FEnumAAGenerator() override;

	/** FBaseGenerator interface */
	virtual FString GetKey() const override;
	virtual bool CanExport()const  override;
	virtual void ExportToMemory() override;
	virtual void FinalizeMemory() override;
	virtual FString GetClassName() const override;
	virtual Type GetType() const override { return Type::UStruct; }

    virtual FString ExportName() const override;
	virtual FString ExportHeaderContent() const override;
	virtual FString ExportConversionRules() const override;
    virtual FString ExportTypeDeclarations() const override;
    virtual bool RequiresImplementation() const override;
	virtual FString ExportAdditionalIncludeDirectives() const override;

	virtual FString ExportBlueprintFunctionLibraryForwardDecl() const override;
	virtual FString ExportBlueprintFunctionLibraryDeclarations() const override;
	virtual FString ExportBlueprintFunctionLibraryDefinitions() const override;

private:
	UEnum* m_enumData;
};


// ABSTRACT_SDK_ENUM_EXTERN_DECLARE(UEEActorGridPlacement, EActorGridPlacement);
// {
// 	ABSTRACT_SDK_ENUM_ENTRY(EActorGridPlacement::Bounds)
// 	EActorGridPlacement::Bounds,
// 	ABSTRACT_SDK_ENUM_ENTRY(EActorGridPlacement::Location)
// 	EActorGridPlacement::Location,
// 	ABSTRACT_SDK_ENUM_ENTRY(EActorGridPlacement::AlwaysLoaded)
// 	EActorGridPlacement::AlwaysLoaded,
// ABSTRACT_SDK_ENUM_EXTERN_DECLARE(UEENetDormancy, ENetDormancy);
// {
// 	ABSTRACT_SDK_ENUM_ENTRY(DORM_Never)
// 	DORM_Never,
// 	ABSTRACT_SDK_ENUM_ENTRY(DORM_Awake)
// 	DORM_Awake,
// 	ABSTRACT_SDK_ENUM_ENTRY(DORM_DormantAll)
// 	DORM_DormantAll,
// 	ABSTRACT_SDK_ENUM_ENTRY(DORM_DormantPartial)
// 	DORM_DormantPartial,
// 	ABSTRACT_SDK_ENUM_ENTRY(DORM_Initial)
// 	DORM_Initial,
// ABSTRACT_SDK_ENUM_EXTERN_DECLARE(UEESpawnActorCollisionHandlingMethod, ESpawnActorCollisionHandlingMethod);
// {
// 	ABSTRACT_SDK_ENUM_ENTRY(ESpawnActorCollisionHandlingMethod::Undefined)
// 	ESpawnActorCollisionHandlingMethod::Undefined,
// 	ABSTRACT_SDK_ENUM_ENTRY(ESpawnActorCollisionHandlingMethod::AlwaysSpawn)
// 	ESpawnActorCollisionHandlingMethod::AlwaysSpawn,
// 	ABSTRACT_SDK_ENUM_ENTRY(ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn)
// 	ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn,
// 	ABSTRACT_SDK_ENUM_ENTRY(ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding)
// 	ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding,
// ABSTRACT_SDK_ENUM_EXTERN_DECLARE(UEEAutoReceiveInput::Type, EAutoReceiveInput::Type);
// {
// 	ABSTRACT_SDK_ENUM_ENTRY(EAutoReceiveInput::Disabled)
// 	EAutoReceiveInput::Disabled,
// 	ABSTRACT_SDK_ENUM_ENTRY(EAutoReceiveInput::Player0)
// 	EAutoReceiveInput::Player0,
// 	ABSTRACT_SDK_ENUM_ENTRY(EAutoReceiveInput::Player1)
// 	EAutoReceiveInput::Player1,
// 	ABSTRACT_SDK_ENUM_ENTRY(EAutoReceiveInput::Player2)
// 	EAutoReceiveInput::Player2,
// 	ABSTRACT_SDK_ENUM_ENTRY(EAutoReceiveInput::Player3)
// 	EAutoReceiveInput::Player3,
// 	ABSTRACT_SDK_ENUM_ENTRY(EAutoReceiveInput::Player4)
// 	EAutoReceiveInput::Player4,
// 	ABSTRACT_SDK_ENUM_ENTRY(EAutoReceiveInput::Player5)
// 	EAutoReceiveInput::Player5,
// 	ABSTRACT_SDK_ENUM_ENTRY(EAutoReceiveInput::Player6)
// 	EAutoReceiveInput::Player6,
// ABSTRACT_SDK_ENUM_EXTERN_DECLARE(UEEPathFollowingStatus::Type, EPathFollowingStatus::Type);
// {
// 	ABSTRACT_SDK_ENUM_ENTRY(EPathFollowingStatus::Idle)
// 	EPathFollowingStatus::Idle,
// 	ABSTRACT_SDK_ENUM_ENTRY(EPathFollowingStatus::Waiting)
// 	EPathFollowingStatus::Waiting,
// 	ABSTRACT_SDK_ENUM_ENTRY(EPathFollowingStatus::Paused)
// 	EPathFollowingStatus::Paused,
