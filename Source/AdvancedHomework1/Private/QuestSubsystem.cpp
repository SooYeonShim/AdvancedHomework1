// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSubsystem.h"
#include "QuestComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SandboxPlayerCharacter.h"

void UQuestSubsystem::NotifyMonsterKilled(AActor* Killer, AActor* Victim)
{
	if (!Killer) return;

	UE_LOG(LogTemp, Warning, TEXT("Monster %s killed by %s. Distributing progress..."), *Victim->GetName(), *Killer->GetName());

	// 일단 모든 플레이어 캐릭터에게 배포하는 방식으로 구현
	TArray<AActor*> PlayerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandboxPlayerCharacter::StaticClass(), PlayerActors);

	for (AActor* Actor : PlayerActors)
	{
		UQuestComponent* QuestComp = Actor->FindComponentByClass<UQuestComponent>();
		if (QuestComp)
		{
			QuestComp->AddKillProgress(1);
		}
	}
}
