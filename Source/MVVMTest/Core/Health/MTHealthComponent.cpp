// Copyright pjdevs. All Rights Reserved.


#include "MTHealthComponent.h"


// Sets default values for this component's properties
UMTHealthComponent::UMTHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	ResetHealth();
}

void UMTHealthComponent::InitializeComponent()
{
	Super::InitializeComponent();

	Health = MaxHealth;

	if (const auto Owner = GetOwner())
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UMTHealthComponent::HandleOwnerTakeAnyDamage);
	}
}

void UMTHealthComponent::UninitializeComponent()
{
	Super::UninitializeComponent();

	if (const auto Owner = GetOwner())
	{
		Owner->OnTakeAnyDamage.RemoveDynamic(this, &UMTHealthComponent::HandleOwnerTakeAnyDamage);
	}
}

void UMTHealthComponent::SetMaxHealth(float NewMaxHealth)
{
	if (NewMaxHealth != MaxHealth)
	{
		MaxHealth = FMath::Max(NewMaxHealth, 0.0f);
		OnMaxHealthChanged.ExecuteIfBound(MaxHealth);
		
		SetHealth(Health);
	}
}

void UMTHealthComponent::SetHealth(float NewHealth)
{
	const float OldHealth = Health;
	
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);

	if (OldHealth != Health)
	{
		OnHealthChanged.ExecuteIfBound(NewHealth);
	}
}

void UMTHealthComponent::ResetHealth()
{
	SetHealth(MaxHealth);
}

void UMTHealthComponent::HandleOwnerTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                                AController* InstigatedBy, AActor* DamageCauser)
{
	SetHealth(Health - Damage);
}
