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

using UnrealBuildTool;
using System;
using System.IO;

public class AbstractAccessibleRuntime : ModuleRules
{
	public AbstractAccessibleRuntime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
				//
            });

		PrivateIncludePaths.AddRange(
			new string[] {
				"AbstractSDKExtern/AbstractSDK/Include",
				"AbstractAccessibleExtern/Source"
			});

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "Engine",
                "CoreUObject",
                "Slate",
                "SlateCore",
				"UnrealEd",
                "InputCore",
				"PhysicsCore",
				"AIModule",
				"NavigationSystem",
				"AbstractSDK",
				"AbstractAccessible",
                // "MyProject",
                "ClothingSystemRuntimeInterface",
				"AudioExtensions",
                "UMG",
				"vs3"
            });

		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../AbstractAccessibleExtern/x64/Debug/AbstractAccessible.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../AbstractSDKExtern/AbstractSDK/x64/Release/AbstractSDK.lib"));
	}
}
