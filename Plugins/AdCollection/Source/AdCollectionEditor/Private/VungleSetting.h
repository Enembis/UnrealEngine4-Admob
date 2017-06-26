// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "VungleSetting.generated.h"

/**
 * 
 */
UCLASS(config = Engine, globaluserconfig)
class UVungleSetting : public UObject
{
	GENERATED_BODY()
	
	
		UPROPERTY(GlobalConfig, EditAnywhere, Category = Android, Meta = (DisplayName = "If Is Vungle Android Enable"))
		bool bAndroidEnabled;

	UPROPERTY(GlobalConfig, EditAnywhere, Category = Android, Meta = (DisplayName = "Vungle Android AppID"))
		FString AndroidAppId;

    
    UPROPERTY(GlobalConfig, EditAnywhere, Category = IOS, Meta = (DisplayName = "If Is Vungle IOS Enable"))
    bool bIOSEnabled;
    
    UPROPERTY(GlobalConfig, EditAnywhere, Category = IOS, Meta = (DisplayName = "Vungle IOS AppID"))
    FString IOSAppId;

#if WITH_EDITOR
	// UObject interface
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
};
