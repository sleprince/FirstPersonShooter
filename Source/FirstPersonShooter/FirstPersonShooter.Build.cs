// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FirstPersonShooter : ModuleRules
{
	public FirstPersonShooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
			"HeadMountedDisplay", "EnhancedInput", "UMG" });

		//For UI added UMG above and the Slate dependencies below
		PrivateDependencyModuleNames.AddRange(new string[]
		{ "Slate", "SlateCore" });

    }
}
