// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h" 
#include "Enemy.generated.h"

UCLASS()
class ADVANCEDHOMEWORK1_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 블루프린트에서 호출할 함수
	UFUNCTION(BlueprintCallable, Category = "AI")
	void PerformAsyncTrace(FVector Start, FVector End);

	// 트레이스 완료 시 호출될 콜백 함수
	void OnTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnPlayerDetected(AActor* DetectedActor);
};
