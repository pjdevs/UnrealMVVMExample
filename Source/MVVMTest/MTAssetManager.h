// Copyright pjdevs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"

#include "MTAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class MVVMTEST_API UMTAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static UMTAssetManager& Get();

	virtual void StartInitialLoading() override;
};
