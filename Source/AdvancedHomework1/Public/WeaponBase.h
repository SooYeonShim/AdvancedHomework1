// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class ADVANCEDHOMEWORK1_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

	UFUNCTION(BlueprintCallable)
	virtual void Fire();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float MaxAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float CurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Stats")
	int32 PelletCount; // 한 발당 총알 개수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Stats")
	float SpreadAngle; // 탄이 퍼지는 각도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Stats")
	float Range; // 사거리
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Stats|Recoil")
	float VerticalRecoil; // 위로 튀는 정도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Stats|Recoil")
	float RecoilDuration; // 반동이 일어나는 시간


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
