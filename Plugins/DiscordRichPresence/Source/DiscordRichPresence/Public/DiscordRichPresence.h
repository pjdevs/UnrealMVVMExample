// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

namespace discord
{
	class Core;
}

class FDiscordRichPresenceModule : public IModuleInterface
{
public:
	static const FName ModuleName;

	static FDiscordRichPresenceModule* Get()
	{
		return static_cast<FDiscordRichPresenceModule*>(FModuleManager::Get().GetModule(ModuleName));
	}

	FORCEINLINE bool IsDiscordSDKLoaded() const { return DiscordGameSDKHandle != nullptr; }

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	// Commands
	static void SetRichPresence();

private:
	static void AddMenuBarExtension(FMenuBarBuilder& Builder);
	static void AddMenuExtension(FMenuBuilder& Builder);

protected:
	FString GetPathToDiscordGameSDKDLL() const;
	
private:
	TSharedPtr<FUICommandList> PluginCommands;
	void* DiscordGameSDKHandle = nullptr;
};
