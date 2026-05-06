// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SandboxWeaponBase.h"
#include "Camera/CameraComponent.h"         
#include "GameFramework/SpringArmComponent.h" 
#include "GameFramework/Character.h"
#include "SandboxPlayerCharacter.generated.h"

UCLASS()
class ADVANCEDHOMEWORK1_API ASandboxPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASandboxPlayerCharacter();

	// 무기 발사 함수
	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void OnStartAiming();

	UFUNCTION(BlueprintCallable)
	void OnStopAiming();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 에디터에서 무기 클래스를 선택하기 위한 변수
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<ASandboxWeaponBase> WeaponClass;

	UPROPERTY()
	ASandboxWeaponBase* CurrentWeapon;

	// C++에서 카메라와 스프링암을 제어할 수 있도록 선언
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArm;

	float TargetFOV = 90.0f;
	float TargetArmLength = 300.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
