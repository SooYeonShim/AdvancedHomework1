// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnQuestUpdated, FString, QuestName, int32, CurrentProgress, int32, TargetProgress);

USTRUCT(BlueprintType)
struct FQuestData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentProgress = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TargetProgress = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCompleted = false;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ADVANCEDHOMEWORK1_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UQuestComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TArray<FQuestData> ActiveQuests;

public:	
	UPROPERTY(BlueprintAssignable, Category = "Quest")
	FOnQuestUpdated OnQuestUpdated;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void AddKillProgress(int32 Amount = 1);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<FQuestData>& GetActiveQuests() const { return ActiveQuests; }
};
