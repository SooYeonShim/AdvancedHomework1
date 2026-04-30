// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ShotgunDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ADVANCEDHOMEWORK1_API UShotgunDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Stats")
	float Damage = 10.0f; // 한 발당 데미지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Stats")
	int32 PelletCount = 8; // 한 발당 총알 개수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Stats")
	float SpreadAngle = 5.0f; // 탄이 퍼지는 각도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Stats")
	float Range = 2000.0f; // 사거리
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Stats|Recoil")
	float VerticalRecoil = -1.5f; // 위로 튀는 정도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Stats|Recoil")
	float RecoilDuration = 0.1f; // 반동이 일어나는 시간
	
};
