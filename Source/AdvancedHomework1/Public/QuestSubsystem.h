// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "QuestSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDHOMEWORK1_API UQuestSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// 몬스터 사망 시 호출
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void NotifyMonsterKilled(AActor* Killer, AActor* Victim);

private:
	// 파티원에게 퀘스트 진행도 전파
	void DistributeProgressToParty(AActor* Killer);
};
