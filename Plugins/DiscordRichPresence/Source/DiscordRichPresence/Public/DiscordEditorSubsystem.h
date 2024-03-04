// Copyright pjdevs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Editor/EditorSubsystem/Public/EditorSubsystem.h"
#include "DiscordRichPresence/ThirdParty/DiscordGameSDK/core.h"
#include "DiscordEditorSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class DISCORDRICHPRESENCE_API UDiscordEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	static UDiscordEditorSubsystem* Get() { return GEditor ? GEditor->GetEditorSubsystem<UDiscordEditorSubsystem>() : nullptr; }

	//~USubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	//~End of USubsystem interface

	void InitDiscord();
	void SetActivity();
	bool Tick(float DeltaTime);
	
private:
	discord::Core* DiscordCore{};
	discord::Activity Activity{};
	FTSTicker::FDelegateHandle TickDelegateHandle{};

	bool bIsInsideEditor = true;
};
