#include "ObjectPool/ObjectPoolSubsystem.h"
#include "ObjectPool/PooledObjectComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

void UObjectPoolSubsystem::InitializePool(const TArray<FPooledObjectData>& Configs)
{
	for (const FPooledObjectData& Config : Configs)
	{
		if (!Config.ActorTemplate) continue;

		FObjectPoolArray& Pool = ObjectPools.FindOrAdd(Config.ActorName);
		Pool.Config = Config;

		for (int32 i = 0; i < Config.PoolSize; ++i)
		{
			AActor* NewActor = CreateNewActor(Config);
			if (NewActor)
			{
				Pool.InactiveActors.Add(NewActor);
			}
		}
	}
}

AActor* UObjectPoolSubsystem::SpawnFromPool(FName Name, FVector Location, FRotator Rotation)
{
	if (!ObjectPools.Contains(Name)) return nullptr;

	FObjectPoolArray& Pool = ObjectPools[Name];
	AActor* ActorToSpawn = nullptr;

	if (Pool.InactiveActors.Num() > 0)
	{
		ActorToSpawn = Pool.InactiveActors.Pop();
	}
	else if (Pool.Config.bCanGrow)
	{
		ActorToSpawn = CreateNewActor(Pool.Config);
	}

	if (ActorToSpawn)
	{
		ActivateActor(ActorToSpawn, Location, Rotation);
		Pool.ActiveActors.Add(ActorToSpawn);
	}

	return ActorToSpawn;
}

void UObjectPoolSubsystem::ReturnToPool(AActor* Actor)
{
	if (!Actor) return;

	UPooledObjectComponent* PoolComp = Actor->FindComponentByClass<UPooledObjectComponent>();
	if (!PoolComp || !PoolComp->IsPoolActive()) return;

	FName PoolName = PoolComp->GetPoolName();
	if (ObjectPools.Contains(PoolName))
	{
		FObjectPoolArray& Pool = ObjectPools[PoolName];
		DeactivateActor(Actor);
		Pool.ActiveActors.Remove(Actor);
		Pool.InactiveActors.Add(Actor);
	}
}

void UObjectPoolSubsystem::ReturnAllToPool()
{
	for (auto& Pair : ObjectPools)
	{
		FObjectPoolArray& Pool = Pair.Value;
		while (Pool.ActiveActors.Num() > 0)
		{
			AActor* Actor = Pool.ActiveActors.Pop();
			DeactivateActor(Actor);
			Pool.InactiveActors.Add(Actor);
		}
	}
}

void UObjectPoolSubsystem::DeactivateActor(AActor* Actor)
{
	if (!Actor) return;

	Actor->SetActorHiddenInGame(true);
	Actor->SetActorEnableCollision(false);
	Actor->SetActorTickEnabled(false);

	Actor->SetActorLocation(FVector(0.0f, 0.0f, -100000.0f));

	if (UPooledObjectComponent* PoolComp = Actor->FindComponentByClass<UPooledObjectComponent>())
	{
		PoolComp->SetPoolActive(false);
	}
}

void UObjectPoolSubsystem::ActivateActor(AActor* Actor, const FVector& Location, const FRotator& Rotation)
{
	if (!Actor) return;

	Actor->SetActorLocationAndRotation(Location, Rotation);
	Actor->SetActorHiddenInGame(false);
	Actor->SetActorEnableCollision(true);
	Actor->SetActorTickEnabled(true);

	if (UPooledObjectComponent* PoolComp = Actor->FindComponentByClass<UPooledObjectComponent>())
	{
		PoolComp->SetPoolActive(true);
	}
}

AActor* UObjectPoolSubsystem::CreateNewActor(const FPooledObjectData& Config)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* NewActor = GetWorld()->SpawnActor<AActor>(Config.ActorTemplate, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (NewActor)
	{
		UPooledObjectComponent* PoolComp = NewActor->FindComponentByClass<UPooledObjectComponent>();
		if (!PoolComp)
		{
			PoolComp = NewObject<UPooledObjectComponent>(NewActor, UPooledObjectComponent::StaticClass());
			PoolComp->RegisterComponent();
		}
		
		if (PoolComp)
		{
			PoolComp->SetPoolName(Config.ActorName);
		}

		DeactivateActor(NewActor);
	}
	return NewActor;
}
