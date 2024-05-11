// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Magician : ModuleRules
{
	public Magician(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory);

		PublicDependencyModuleNames.AddRange(new string[] 
		{ "Core", "CoreUObject", "Engine", "InputCore" }
		);
	}
}
