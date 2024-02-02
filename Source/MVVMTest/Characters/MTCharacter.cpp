// Copyright pjdevs. All Rights Reserved.


#include "MTCharacter.h"

#include "Components/WidgetComponent.h"
#include "MVVMSubsystem.h"
#include "View/MVVMView.h"
#include "MVVMTest/Core/HealthComponent.h"
#include "MVVMTest/UI/ViewModels/MVVMViewModelHealth.h"


// Sets default values
AMTCharacter::AMTCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = CreateDefaultSubobject<UHealthComponent>("Health");
	
	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>("Health Bar Widget");
	HealthBarWidget->SetupAttachment(RootComponent);
}

// Called every frame
void AMTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMTCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ViewModelHealth = NewObject<UMVVMViewModelHealth>(this);
	ViewModelHealth->SetMaxHealth(Health->GetMaxHealth());
	ViewModelHealth->SetHealth(Health->GetHealth());
	
	Health->OnHealthChanged.BindLambda([this](float NewHealth)
	{
		ViewModelHealth->SetHealth(NewHealth);
	});
	Health->OnMaxHealthChanged.BindLambda([this](float NewMaxHealth)
	{
		ViewModelHealth->SetMaxHealth(NewMaxHealth);
	});
}

void AMTCharacter::BeginPlay()
{
	Super::BeginPlay();

	const TObjectPtr<UMVVMSubsystem> ViewModelSubsystem = GEngine->GetEngineSubsystem<UMVVMSubsystem>();
	check(ViewModelSubsystem);

	if (const TObjectPtr<UMVVMView> HealthView = ViewModelSubsystem->GetViewFromUserWidget(HealthBarWidget->GetWidget()))
	{
		HealthView->SetViewModel(FName("MVVMViewModelHealth"), ViewModelHealth);
	}
}