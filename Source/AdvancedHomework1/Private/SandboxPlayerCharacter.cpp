// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPlayerCharacter.h"

// Sets default values
ASandboxPlayerCharacter::ASandboxPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    WeaponClass = nullptr;

    // 1. 스프링암 생성 및 설정
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent); // 캡슐 컴포넌트(Root)에 부착
    SpringArm->TargetArmLength = 300.0f;       // 기본 거리

    // 2. 카메라 생성 및 스프링암에 부착
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(SpringArm);

    // 3. 헬스 컴포넌트 생성
    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

    // 4. 퀘스트 컴포넌트 생성
    QuestComponent = CreateDefaultSubobject<UQuestComponent>(TEXT("QuestComponent"));
}

void ASandboxPlayerCharacter::StartFire()
{
    // 무기가 유효한지 확인 후 발사
    if (CurrentWeapon)
    {
        CurrentWeapon->Fire();
    }
}

void ASandboxPlayerCharacter::OnStartAiming()
{
    if (CurrentWeapon) CurrentWeapon->SetAiming(true);

    // 조준 시작: 타겟 FOV를 60으로 설정 (Tick이 알아서 90 -> 60으로 이동시킴)
    TargetFOV = 60.0f;
    TargetArmLength = 100.f;
}

void ASandboxPlayerCharacter::OnStopAiming()
{
    if (CurrentWeapon) CurrentWeapon->SetAiming(false);

    // 조준 해제: 타겟 FOV를 다시 90으로 설정 (Tick이 알아서 60 -> 90으로 복구시킴)
    TargetFOV = 90.0f;
    TargetArmLength = 300.f;
}

void ASandboxPlayerCharacter::HandleDeath()
{
    // 사망 처리 로직
    UE_LOG(LogTemp, Warning, TEXT("Player is DEAD!"));
    
    // 입력을 비활성화하거나 봉인
    APlayerController* PC = Cast<APlayerController>(GetController());
    if (PC)
    {
        DisableInput(PC);
    }

    // 래그돌 설정
    GetMesh()->SetSimulatePhysics(true);
    GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
    
    // 무기 부착 해제 등 추가 작업 가능
}

// Called when the game starts or when spawned
void ASandboxPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

    if (HealthComponent)
    {
        HealthComponent->OnHealthDead.AddDynamic(this, &ASandboxPlayerCharacter::HandleDeath);
    }


    // 무기 스폰 및 부착 로직
    if (WeaponClass)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this; // 캐릭터를 주인으로 설정
        SpawnParams.Instigator = GetInstigator();

        // 무기 스폰
        CurrentWeapon = GetWorld()->SpawnActor<ASandboxWeaponBase>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

        // 캐릭터 메쉬의 소켓에 부착
        if (CurrentWeapon)
        {
            FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
            CurrentWeapon->AttachToComponent(GetMesh(), AttachmentRules, FName("weapon_r_muzzle"));
        }
    }
}

// Called every frame
void ASandboxPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    // 현재 FOV에서 타겟 FOV까지 부드럽게 보간 (FInterpTo)
    float CurrentFOV = FollowCamera->FieldOfView;
    FollowCamera->SetFieldOfView(FMath::FInterpTo(CurrentFOV, TargetFOV, DeltaTime, 10.0f));

    // 2. SpringArm 거리 보간
    float CurrentArmLength = SpringArm->TargetArmLength;
    SpringArm->TargetArmLength = FMath::FInterpTo(CurrentArmLength, TargetArmLength, DeltaTime, 10.0f);
}

// Called to bind functionality to input
void ASandboxPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

