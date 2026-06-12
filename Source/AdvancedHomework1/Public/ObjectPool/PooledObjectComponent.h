#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PooledObjectComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPooledObjectActivatedSignature);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ADVANCEDHOMEWORK1_API UPooledObjectComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPooledObjectComponent();

	UPROPERTY(BlueprintAssignable, Category = "Object Pool")
	FPooledObjectActivatedSignature OnObjectActivated;

	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	void ReturnToPool();

	bool IsPoolActive() const { return bIsPoolActive; }
	void SetPoolActive(bool bActive);

	FName GetPoolName() const { return PoolName; }
	void SetPoolName(FName InName) { PoolName = InName; }

private:
	UPROPERTY(VisibleAnywhere, Category = "Object Pool")
	bool bIsPoolActive = false;

	UPROPERTY(VisibleAnywhere, Category = "Object Pool")
	FName PoolName;
};
