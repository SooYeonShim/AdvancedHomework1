// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxWeaponBase.h"
#include "GameFramework/Character.h"        // ACharacter 클래스 정의
#include "Kismet/GameplayStatics.h"

void ASandboxWeaponBase::Fire()
{
	SandboxFire();
}

void ASandboxWeaponBase::LinetraceOneShot(FVector Direction)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		ACharacter* MyCharacter = Cast<ACharacter>(MyOwner);
		if (MyCharacter)
		{
			// 캐릭터의 GetMesh()를 호출
			USkeletalMeshComponent* CharacterMesh = MyCharacter->GetMesh();

			// 소켓 위치 가져오기
			FHitResult Hit(ForceInit); // ForceInit으로 강제 초기화 가능
			FVector Start = CharacterMesh->GetSocketLocation(FName("weapon_r_muzzle"));
			FVector End = Start + (Direction * Range);

			UKismetSystemLibrary::LineTraceSingle(
				this,
				Start,
				End,
				UEngineTypes::ConvertToTraceType(ECC_Visibility),
				false,
				{ this, GetOwner() },
				EDrawDebugTrace::ForDuration,
				Hit,
				true,
				FLinearColor::Red,
				FLinearColor::Green,
				5.f
			);
		}
	}
}

void ASandboxWeaponBase::PlaySound(USoundBase* Sound)
{
	UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());
}


void ASandboxWeaponBase::Reload()
{
	CurrentAmmo = MaxAmmo;
}

void ASandboxWeaponBase::UpdateAmmo()
{
	CurrentAmmo -= PelletCount;
}

void ASandboxWeaponBase::SetAiming(bool bNewAiming)
{
	bIsAiming = bNewAiming;

	// 조준 중일 때의 로직 (예: 탄퍼짐 감소)
	if (bIsAiming) {
		// CurrentSpread *= 0.5f; 
	}
}

