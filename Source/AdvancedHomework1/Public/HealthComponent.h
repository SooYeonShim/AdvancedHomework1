// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthDamaged, float, CurrentHealth, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthDead);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthDeadWithInstigator, AActor*, Killer);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ADVANCEDHOMEWORK1_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float CurrentHealth;

public:	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthDamaged OnHealthDamaged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthDead OnHealthDead;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthDeadWithInstigator OnHealthDeadWithInstigator;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float DamageAmount, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const { return CurrentHealth / MaxHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const { return CurrentHealth <= 0.0f; }
};
