// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DiscordRichPresenceCommands.h"

#define LOCTEXT_NAMESPACE "FDiscordRichPresenceModule"

void FDiscordRichPresenceCommands::RegisterCommands()
{
	UI_COMMAND(ResetRichPresenceAction, "Set Discord Rich Presence", "Send Discord Rich Prensence to client", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE