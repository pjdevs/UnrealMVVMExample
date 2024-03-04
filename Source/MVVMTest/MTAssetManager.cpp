// Copyright pjdevs. All Rights Reserved.


#include "MTAssetManager.h"
#include "AbilitySystemGlobals.h"
#include "GameplayTags.h"


UMTAssetManager& UMTAssetManager::Get() 
{
	UMTAssetManager* Singleton = Cast<UMTAssetManager>(GEngine->AssetManager);

	if (Singleton)
	{
		return *Singleton;
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini, must be MTAssetManager!"));
		return *NewObject<UMTAssetManager>();	 // never calls this
	}
}


void UMTAssetManager::StartInitialLoading() 
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();

	FMTGameplayTags::StateDead = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	FMTGameplayTags::StateDebuffStun = FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun"));
}