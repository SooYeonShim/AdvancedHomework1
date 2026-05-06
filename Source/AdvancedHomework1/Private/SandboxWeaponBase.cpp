// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxWeaponBase.h"
#include "GameFramework/Character.h"        // ACharacter 클래스 정의
#include "Camera/CameraComponent.h"
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
			FVector SocketLocation = CharacterMesh->GetSocketLocation(FName("weapon_r_muzzle"));
			UE_LOG(LogTemp, Warning, TEXT("Socket Location: %s"), *SocketLocation.ToString());	
			// 소켓 위치 가져오기
			FHitResult Hit(ForceInit); // ForceInit으로 강제 초기화 가능
			UCameraComponent* Camera = MyCharacter->FindComponentByClass<UCameraComponent>();
			if (!Camera) return;

			// 2. 조준점은 카메라의 위치에서 시작합니다.
			FVector Start = Camera->GetComponentLocation();

			// 3. 방향은 카메라가 바라보는 방향(ForwardVector)으로 고정!
			FVector End = Start + (Camera->GetForwardVector() * Range);

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

