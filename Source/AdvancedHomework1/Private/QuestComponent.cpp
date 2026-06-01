// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestComponent.h"

UQuestComponent::UQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UQuestComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// 기본 퀘스트로 100마리 몬스터 처치 추가
	FQuestData KillQuest;
	KillQuest.QuestName = TEXT("Kill 100 Monsters");
	KillQuest.TargetProgress = 100;
	ActiveQuests.Add(KillQuest);
}

void UQuestComponent::AddKillProgress(int32 Amount)
{
	for (FQuestData& Quest : ActiveQuests)
	{
		if (!Quest.bIsCompleted && Quest.QuestName.Contains(TEXT("Kill")))
		{
			Quest.CurrentProgress = FMath::Min(Quest.CurrentProgress + Amount, Quest.TargetProgress);
			
			if (Quest.CurrentProgress >= Quest.TargetProgress)
			{
				Quest.bIsCompleted = true;
				UE_LOG(LogTemp, Warning, TEXT("Quest Completed: %s"), *Quest.QuestName);
			}

			OnQuestUpdated.Broadcast(Quest.QuestName, Quest.CurrentProgress, Quest.TargetProgress);
		}
	}
}
