// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxWeaponBase.h"
#include "GameFramework/Character.h"        // ACharacter Ŭ 
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"

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
			// 캐릭터 메쉬에서 소켓 위치 가져오기
			USkeletalMeshComponent* CharacterMesh = MyCharacter->GetMesh();
			FVector SocketLocation = CharacterMesh->GetSocketLocation(FName("weapon_r_muzzle"));

			// 히트 결과 및 레이캐스트 설정
			FHitResult Hit(ForceInit); 
			UCameraComponent* Camera = MyCharacter->FindComponentByClass<UCameraComponent>();
			if (!Camera) return;

			FVector Start = Camera->GetComponentLocation();
			FVector End = Start + (Direction * Range); // Use passed direction

			if (UKismetSystemLibrary::LineTraceSingle(
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
			))
			{
				AActor* HitActor = Hit.GetActor();
				if (HitActor)
				{
					UHealthComponent* HitHealth = HitActor->FindComponentByClass<UHealthComponent>();
					if (HitHealth)
					{
						// Default damage if no data asset is found, or we can pass it from BP
						float DamageToApply = 10.0f; 
						HitHealth->TakeDamage(DamageToApply, GetOwner());
					}
				}
			}
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

	// ���� ���� ���� ���� (��: ź���� ����)
	if (bIsAiming) {
		// CurrentSpread *= 0.5f; 
	}
}

