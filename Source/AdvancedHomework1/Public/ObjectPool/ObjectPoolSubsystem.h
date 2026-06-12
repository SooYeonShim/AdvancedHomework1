#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PooledObjectData.h"
#include "ObjectPoolSubsystem.generated.h"

USTRUCT()
struct FObjectPoolArray
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AActor*> InactiveActors;

	UPROPERTY()
	TArray<AActor*> ActiveActors;

	UPROPERTY()
	FPooledObjectData Config;
};

UCLASS()
class ADVANCEDHOMEWORK1_API UObjectPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	void InitializePool(const TArray<FPooledObjectData>& Configs);

	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	AActor* SpawnFromPool(FName Name, FVector Location, FRotator Rotation);

	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	void ReturnToPool(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	void ReturnAllToPool();

private:
	UPROPERTY()
	TMap<FName, FObjectPoolArray> ObjectPools;

	void DeactivateActor(AActor* Actor);
	void ActivateActor(AActor* Actor, const FVector& Location, const FRotator& Rotation);
	AActor* CreateNewActor(const FPooledObjectData& Config);
};
