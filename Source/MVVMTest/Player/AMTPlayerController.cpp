// Copyright pjdevs. All Rights Reserved.


#include "AMTPlayerController.h"

#include "AbilitySystemComponent.h"
#include "MVVMTest/Characters/MTCharacter.h"

void AAMTPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	if (const IAbilitySystemInterface* AbilityPawn = Cast<IAbilitySystemInterface>(P))
	{
		AbilityPawn->GetAbilitySystemComponent()->InitAbilityActorInfo(P, P);	
	}
}
