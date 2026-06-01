// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h" 
#include "HealthComponent.h"
#include "Enemy.generated.h"

UCLASS()
class ADVANCEDHOMEWORK1_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	UHealthComponent* HealthComponent;

	UFUNCTION()
	void HandleDeath(AActor* Killer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ��������Ʈ���� ȣ���� �Լ�
	UFUNCTION(BlueprintCallable, Category = "AI")
	void PerformAsyncTrace(FVector Start, FVector End);

	// Ʈ���̽� �Ϸ� �� ȣ��� �ݹ� �Լ�
	void OnTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnPlayerDetected(AActor* DetectedActor);
};
