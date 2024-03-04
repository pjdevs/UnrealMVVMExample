// Copyright Epic Games, Inc. All Rights Reserved.

#include "DiscordRichPresence.h"

#include "DiscordEditorSubsystem.h"
#include "DiscordRichPresenceCommands.h"
#include "Modules/ModuleManager.h"
#include "LevelEditor.h"
#include "Framework/MultiBox/MultiBoxExtender.h"
#include "Interfaces/IPluginManager.h"

const FName FDiscordRichPresenceModule::ModuleName("DiscordRichPresence");

#define LOCTEXT_NAMESPACE "FDiscordRichPresenceModule"

void FDiscordRichPresenceModule::StartupModule()
{
	FDiscordRichPresenceCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FDiscordRichPresenceCommands::Get().ResetRichPresenceAction,
		FExecuteAction::CreateStatic(&FDiscordRichPresenceModule::SetRichPresence),
		FCanExecuteAction());
	
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
	MenuExtender->AddMenuBarExtension("Help", EExtensionHook::After, PluginCommands, FMenuBarExtensionDelegate::CreateStatic(&FDiscordRichPresenceModule::AddMenuBarExtension));

	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	
	const FString LibraryPath = GetPathToDiscordGameSDKDLL();
    DiscordGameSDKHandle = FPlatformProcess::GetDllHandle(*LibraryPath);
}

void FDiscordRichPresenceModule::ShutdownModule()
{
	if (DiscordGameSDKHandle)
	{
		FPlatformProcess::FreeDllHandle(DiscordGameSDKHandle);
		DiscordGameSDKHandle = nullptr;
	}
}

void FDiscordRichPresenceModule::SetRichPresence()
{
	if (const auto Subsystem = UDiscordEditorSubsystem::Get())
	{
		Subsystem->InitDiscord();

		const FText DialogText = LOCTEXT("RichPresenceResetText", "Rich presence reset.");
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);
	}
	else
	{
		const FText DialogText = LOCTEXT("RichPresenceNoneText", "Failed. Subsystem is not loaded.");
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);
	}
}

void FDiscordRichPresenceModule::AddMenuBarExtension(FMenuBarBuilder& Builder)
{
	Builder.AddPullDownMenu(
		LOCTEXT("DiscordRichPresenceMenuKey", "DiscordRichPresence"),
		LOCTEXT("DiscordRichPresenceMenuTooltipKey", "Opens menu for DiscordRichPresence"),
		FNewMenuDelegate::CreateStatic(&FDiscordRichPresenceModule::AddMenuExtension));
	
}

void FDiscordRichPresenceModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FDiscordRichPresenceCommands::Get().ResetRichPresenceAction);
}

FString FDiscordRichPresenceModule::GetPathToDiscordGameSDKDLL() const
{
	const FString BaseDir =  IPluginManager::Get().FindPlugin(ModuleName.ToString())->GetBaseDir();
	FString LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/DiscordGameSDK"));
	
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*LibraryPath, TEXT("Win64/discord_game_sdk.dll"));
#elif PLATFORM_MAC
	LibraryPath = FPaths::Combine(*LibraryPath, TEXT("Mac/discord_game_sdk.dylib"));
#elif PLATFORM_LINUX
	LibraryPath = FPaths::Combine(*LibraryPath, TEXT("Linux/discord_game_sdk.so"));
#endif

	return LibraryPath;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDiscordRichPresenceModule, DiscordRichPresence)
