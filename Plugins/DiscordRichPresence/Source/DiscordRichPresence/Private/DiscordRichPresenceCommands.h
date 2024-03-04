// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SlateBasics.h"


class FDiscordRichPresenceCommands : public TCommands<FDiscordRichPresenceCommands>
{
public:

	FDiscordRichPresenceCommands()
		: TCommands(
			TEXT("DiscordRichPresence"),
			NSLOCTEXT("Contexts", "DiscordRichPresence", "DiscordRichPresence Plugin"),
			NAME_None,
			FName("Default"))
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > ResetRichPresenceAction;
};