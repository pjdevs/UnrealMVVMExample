// Copyright pjdevs. All Rights Reserved.


#include "DiscordEditorSubsystem.h"
#include "DiscordRichPresence.h"

static void DiscordLog(discord::LogLevel Level, const char* Msg)
{
	UE_LOG(LogTemp, Display, TEXT("DiscordLog: Level %d: %hs"), static_cast<int>(Level), Msg);
}


void UDiscordEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	InitDiscord();
}

void UDiscordEditorSubsystem::Deinitialize()
{
	FTSTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
	
	Super::Deinitialize();
}

void UDiscordEditorSubsystem::InitDiscord()
{
	if (const FDiscordRichPresenceModule* DRPModule = FDiscordRichPresenceModule::Get(); !DRPModule || !DRPModule->IsDiscordSDKLoaded())
		return;

	DiscordCore = nullptr;

	discord::Result Result = discord::Core::Create(1214069031535902732, DiscordCreateFlags_Default, &DiscordCore);
    	
	if (Result != discord::Result::Ok)
	{
		UE_LOG(LogTemp, Error, TEXT("Discord Core creation failed with result %d"), static_cast<int>(Result));
		DiscordCore = nullptr;
		return;
	}

	DiscordCore->SetLogHook(discord::LogLevel::Debug, DiscordLog);
	DiscordCore->SetLogHook(discord::LogLevel::Info, DiscordLog);
	DiscordCore->SetLogHook(discord::LogLevel::Warn, DiscordLog);
	DiscordCore->SetLogHook(discord::LogLevel::Error, DiscordLog);
	
	Activity.SetName("Unreal Engine Editor");
	Activity.SetState("Inside the editor");
	Activity.GetAssets().SetSmallImage("");
	Activity.GetAssets().SetSmallText("");
	Activity.GetAssets().SetLargeImage("ue_logo_white");
	Activity.GetAssets().SetLargeText("Unreal Engine");
	Activity.SetType(discord::ActivityType::Playing);
	
	TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &ThisClass::Tick));

	SetActivity();
}

void UDiscordEditorSubsystem::SetActivity()
{
	if (bIsInsideEditor)
	{
		Activity.SetDetails("");
		Activity.SetState("Inside the editor");
	}
	else
	{
		Activity.SetDetails("Programming");
		Activity.SetState("Outside the editor");
	}
	
	DiscordCore->ActivityManager().UpdateActivity(Activity, [](const discord::Result Result)
	{
		UE_LOG(LogTemp, Display, TEXT("Activity set with result %d"), static_cast<int>(Result));
	});
}

bool UDiscordEditorSubsystem::Tick(float DeltaTime)
{
	if (DiscordCore == nullptr)
		return true;

	const bool bWasInsideEditor = bIsInsideEditor;
	bIsInsideEditor = GEditor ? !GEditor->AreAllWindowsHidden() : false;

	if (bWasInsideEditor != bIsInsideEditor)
	{
		SetActivity();
	}
	
	DiscordCore->RunCallbacks();

	return true;
}
