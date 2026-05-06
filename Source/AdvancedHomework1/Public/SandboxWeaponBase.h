// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "SandboxWeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDHOMEWORK1_API ASandboxWeaponBase : public AWeaponBase
{
	GENERATED_BODY()

public:
	virtual void Fire() override;

	UFUNCTION(BlueprintImplementableEvent)
	void SandboxFire();

	UFUNCTION(BlueprintCallable)
	void LinetraceOneShot(FVector Direction);

	// »ç¿îµå
	UFUNCTION(BlueprintCallable)
	void PlaySound(USoundBase* Sound);

	UFUNCTION(BlueprintCallable)
	void Reload();

	UFUNCTION(BlueprintCallable)
	void UpdateAmmo();

	UFUNCTION(BlueprintCallable)
	void SetAiming(bool bNewAiming);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bIsAiming = false;

	
};
