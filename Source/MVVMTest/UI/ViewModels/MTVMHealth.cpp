// Copyright pjdevs. All Rights Reserved.


#include "MTVMHealth.h"

void UMTVMHealth::SetHealth(float NewHealth)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(Health, NewHealth))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}
}

void UMTVMHealth::SetMaxHealth(float NewMaxHealth)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxHealth, NewMaxHealth))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}
}

float UMTVMHealth::GetHealthPercent() const
{
	if (MaxHealth != 0)
	{
		return Health / MaxHealth;
	}

	return 0;
}
