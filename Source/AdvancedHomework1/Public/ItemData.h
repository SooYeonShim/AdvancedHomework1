// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemData
{
    GENERATED_BODY()

    // 아이템 ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 ItemID;

    // 아이템 이름
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString RequiredTitle;

    // 아이템 설명
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString Description;

    // 아이템 수량
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 Count;
};