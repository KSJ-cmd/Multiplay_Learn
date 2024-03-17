// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Multiplay_Learn : ModuleRules
{
	public Multiplay_Learn(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput","UMG", "OnlineSubsystem" });
	}
}
