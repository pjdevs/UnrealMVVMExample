// Copyright (c) 2024 xist.gg

using System.IO;
using UnrealBuildTool;

public class DiscordGameSDK : ModuleRules
{
	public DiscordGameSDK(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "discord_game_sdk.dll.lib"));

			// Delay-load the DLL, so we can load it from the right place first
			PublicDelayLoadDLLs.Add("discord_game_sdk.dll");

			// Ensure that the DLL is staged along with the executable
			RuntimeDependencies.Add("$(TargetOutputDir)/discord_game_sdk.dll", "$(PluginDir)/Source/ThirdParty/DiscordGameSDK/Win64/discord_game_sdk.dll");
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "discord_game_sdk.dylib"));
			RuntimeDependencies.Add("$(TargetOutputDir)/discord_game_sdk.dylib", Path.Combine("$(PluginDir)/Source/ThirdParty/DiscordGameSDK/Mac/discord_game_sdk.dylib"));
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			string soPath = "$(PluginDir)/Source/ThirdParty/DiscordGameSDK/Linux/x86_64-unknown-linux-gnu/discord_game_sdk.so";
			PublicAdditionalLibraries.Add(soPath);
			PublicDelayLoadDLLs.Add(soPath);
			RuntimeDependencies.Add("$(TargetOutputDir)/discord_game_sdk.so", soPath);
		}
	}
}