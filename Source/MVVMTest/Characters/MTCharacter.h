// Copyright pjdevs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "MVVMTest/TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "MTCharacter.generated.h"

class UMTAbilitySystemComponent;
class UWidgetComponent;
class UMTVMHealth;
class UMTHealthComponent;

UCLASS(ClassGroup=Game)
class MVVMTEST_API AMTCharacter : public ATP_ThirdPersonCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Ability system component of the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	UMTAbilitySystemComponent* AbilitySystemComponent;
	
	/** Health component of the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	UMTHealthComponent* Health;

	/** Health component of the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HealthBarWidget;
	
	/** Health view model */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	UMTVMHealth* ViewModelHealth;
	
public:
	// Sets default values for this character's properties
	AMTCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	// Possession on server
	virtual void PossessedBy(AController* NewController) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	void DebugStun() const;

	UFUNCTION(BlueprintCallable)
	void DebugUnStun() const;
	
protected:
	virtual void BeginPlay() override;

private:
	void OnStunChanged(FGameplayTag GameplayTag, int Count) const;
};
