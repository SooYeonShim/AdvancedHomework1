#pragma once

#include "CoreMinimal.h"
#include "PooledObjectData.generated.h"

USTRUCT(BlueprintType)
struct ADVANCEDHOMEWORK1_API FPooledObjectData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Pool")
	TSubclassOf<AActor> ActorTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Pool")
	int32 PoolSize = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Pool")
	bool bCanGrow = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Pool")
	FName ActorName;
};
