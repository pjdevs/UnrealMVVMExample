// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class DiscordRichPresence : ModuleRules
{
	public DiscordRichPresence(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"Projects",
			"SlateCore",
			"Slate",
			"UnrealEd",
			"EditorSubsystem",
			"LevelEditor",
			"DiscordGameSDK"
		});
	}
}
