// Copyright pjdevs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "UObject/Object.h"
#include "MVVMViewModelHealth.generated.h"

/**
 * Health view model
 */
UCLASS(BlueprintType, ClassGroup=(Game))
class MVVMTEST_API UMVVMViewModelHealth : public UMVVMViewModelBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta=(AllowPrivateAccess))
	float MaxHealth;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta=(AllowPrivateAccess))
	float Health;

public:
	float GetHealth() const { return Health; }
	float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetHealthPercent() const;
	
	void SetHealth(float NewHealth);
	void SetMaxHealth(float NewMaxHealth);
};
