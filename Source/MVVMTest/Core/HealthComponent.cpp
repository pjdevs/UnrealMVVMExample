// Copyright pjdevs. All Rights Reserved.


#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	ResetHealth();
}

void UHealthComponent::InitializeComponent()
{
	Super::InitializeComponent();

	Health = MaxHealth;

	if (const auto Owner = GetOwner())
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleOwnerTakeAnyDamage);
	}
}

void UHealthComponent::UninitializeComponent()
{
	Super::UninitializeComponent();

	if (const auto Owner = GetOwner())
	{
		Owner->OnTakeAnyDamage.RemoveDynamic(this, &UHealthComponent::HandleOwnerTakeAnyDamage);
	}
}

void UHealthComponent::SetMaxHealth(float NewMaxHealth)
{
	if (NewMaxHealth != MaxHealth)
	{
		MaxHealth = FMath::Max(NewMaxHealth, 0.0f);
		OnMaxHealthChanged.ExecuteIfBound(MaxHealth);
		
		SetHealth(Health);
	}
}

void UHealthComponent::SetHealth(float NewHealth)
{
	const float OldHealth = Health;
	
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);

	if (OldHealth != Health)
	{
		OnHealthChanged.ExecuteIfBound(NewHealth);
	}
}

void UHealthComponent::ResetHealth()
{
	SetHealth(MaxHealth);
}

void UHealthComponent::HandleOwnerTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                                AController* InstigatedBy, AActor* DamageCauser)
{
	SetHealth(Health - Damage);
}
