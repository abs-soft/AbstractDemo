// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class vs3EditorTarget : TargetRules
{
	public vs3EditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "vs3" } );
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
	}
}
