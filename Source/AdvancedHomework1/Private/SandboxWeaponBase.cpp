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
	if (!MyOwner) return;

	ACharacter* MyCharacter = Cast<ACharacter>(MyOwner);
	if (!MyCharacter) return;

	// 플레이어의 컨트롤러 회전값(조준 방향)을 가져옴
	FRotator AimRotation = MyCharacter->GetControlRotation();
	FVector AimDirection = AimRotation.Vector();

	// 총알이 시작될 위치 (캐릭터의 무기 소켓 위치)
	FVector Start = MyCharacter->GetMesh()->GetSocketLocation(FName("weapon_r_muzzle"));
	
	// 소켓 위치가 잘못되었다면 캐릭터 위치에서 약간 위쪽(눈높이)에서 시작
	if (Start.IsZero())
	{
		Start = MyCharacter->GetActorLocation() + FVector(0, 0, 60.0f);
	}

	FVector End = Start + (AimDirection * 15000.0f);

	FHitResult Hit(ForceInit); 
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(MyOwner);

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Camera, Params);

	// 디버그 라인: 이제 총구에서 조준점 방향으로 정확히 나갑니다.
	DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Green : FColor::Red, false, 1.0f, 0, 1.0f);

	if (bHit)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("HIT: %s"), *HitActor->GetName());
			
			UHealthComponent* HitHealth = HitActor->FindComponentByClass<UHealthComponent>();
			if (HitHealth)
			{
				HitHealth->TakeDamage(34.0f, MyOwner);
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

