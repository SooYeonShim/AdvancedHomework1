// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemData.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ADVANCEDHOMEWORK1_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RegisterItem(const FItemData& NewItemInfo);
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// 가방
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<FItemData> Inventory;

	// 아이템 정보 조회	
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TMap<int32, FItemData> ItemMap;

	// 칭호
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TSet<FString> Titles;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddItemByID(int32 ItemID, int32 Amount);
	UFUNCTION(BlueprintCallable)
	bool UseItem(int32 ItemID);
	UFUNCTION(BlueprintCallable, Category = "Title")
	void AddTitle(const FString& Title);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FItemData GetItemInfo(int32 ItemID);

	FTimerHandle TitleTimerHandle;
		
};
