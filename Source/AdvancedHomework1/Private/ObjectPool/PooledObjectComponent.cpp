#include "ObjectPool/PooledObjectComponent.h"
#include "ObjectPool/ObjectPoolSubsystem.h"
#include "GameFramework/Actor.h"

UPooledObjectComponent::UPooledObjectComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPooledObjectComponent::ReturnToPool()
{
	if (UWorld* World = GetWorld())
	{
		if (UObjectPoolSubsystem* PoolSubsystem = World->GetSubsystem<UObjectPoolSubsystem>())
		{
			PoolSubsystem->ReturnToPool(GetOwner());
		}
	}
}

void UPooledObjectComponent::SetPoolActive(bool bActive)
{
	bIsPoolActive = bActive;
	if (bIsPoolActive)
	{
		OnObjectActivated.Broadcast();
	}
}
