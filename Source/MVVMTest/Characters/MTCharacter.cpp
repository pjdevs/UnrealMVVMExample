// Copyright pjdevs. All Rights Reserved.


#include "MTCharacter.h"

#include "Components/WidgetComponent.h"
#include "MVVMSubsystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MVVMTest/GameplayTags.h"
#include "MVVMTest/Core/Abilities/MTAbilitySystemComponent.h"
#include "View/MVVMView.h"
#include "MVVMTest/Core/Health/MTHealthComponent.h"
#include "MVVMTest/UI/ViewModels/MTVMHealth.h"


// Sets default values
AMTCharacter::AMTCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UMTAbilitySystemComponent>("Ability System Component");
	AbilitySystemComponent->SetIsReplicated(true);
	
	Health = CreateDefaultSubobject<UMTHealthComponent>("Health");
	
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

	AbilitySystemComponent->RegisterGameplayTagEvent(FMTGameplayTags::StateDebuffStun, EGameplayTagEventType::NewOrRemoved)
		.AddUObject(this, &AMTCharacter::OnStunChanged);
	
	ViewModelHealth = NewObject<UMTVMHealth>(this);
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

void AMTCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	SetOwner(NewController);
}

UAbilitySystemComponent* AMTCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMTCharacter::DebugStun() const
{
	AbilitySystemComponent->AddReplicatedLooseGameplayTag(FMTGameplayTags::StateDebuffStun);
}

void AMTCharacter::DebugUnStun() const
{
	AbilitySystemComponent->RemoveReplicatedLooseGameplayTag(FMTGameplayTags::StateDebuffStun);
}

void AMTCharacter::BeginPlay()
{
	Super::BeginPlay();

	const TObjectPtr<UMVVMSubsystem> ViewModelSubsystem = GEngine->GetEngineSubsystem<UMVVMSubsystem>();
	check(ViewModelSubsystem);

	if (const TObjectPtr<UMVVMView> HealthView = ViewModelSubsystem->GetViewFromUserWidget(HealthBarWidget->GetWidget()))
	{
		HealthView->SetViewModel(FName("ViewModel"), ViewModelHealth);
	}
}

void AMTCharacter::OnStunChanged(FGameplayTag GameplayTag, int Count) const
{
	if (Count > 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 100.0f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
}
