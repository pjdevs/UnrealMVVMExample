// Copyright pjdevs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DELEGATE_OneParam(FHealthChangedDelegate, float);
DECLARE_DELEGATE_OneParam(FMaxHealthChangedDelegate, float);

/** Basic Health component */
UCLASS(ClassGroup=(Game), meta=(BlueprintSpawnableComponent))
class MVVMTEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FMaxHealthChangedDelegate OnMaxHealthChanged;
	FHealthChangedDelegate OnHealthChanged;
	
private:
	/** Max and default health */
	float MaxHealth = 100.0f;
	
	/** The current health */
	float Health;

public:
	// Sets default values for this component's properties
	UHealthComponent();

	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	
	/** Get the current health */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetHealth() const { return Health; }

	/** Get the max health */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	/** Set max health */
	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float NewMaxHealth);

	/** Set health */
	UFUNCTION(BlueprintCallable)
	void SetHealth(float NewHealth);
	
	/** Reset health to max health */
	UFUNCTION(BlueprintCallable)
	void ResetHealth();
	
private:
	UFUNCTION()
	void HandleOwnerTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	                              AController* InstigatedBy, AActor* DamageCauser);
	
};
