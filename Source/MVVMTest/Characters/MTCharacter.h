// Copyright pjdevs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMTest/TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "MTCharacter.generated.h"

class UWidgetComponent;
class UMVVMViewModelHealth;
class UHealthComponent;

UCLASS(ClassGroup=Game)
class MVVMTEST_API AMTCharacter : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()

	/** Health component of the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	UHealthComponent* Health;

	/** Health component of the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HealthBarWidget;
	
	/** Health view model */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	UMVVMViewModelHealth* ViewModelHealth;
	
public:
	// Sets default values for this character's properties
	AMTCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

protected:
	void BeginPlay() override;
};
