// Copyright pjdevs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AMTPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MVVMTEST_API AAMTPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void AcknowledgePossession(APawn* P) override;
};
