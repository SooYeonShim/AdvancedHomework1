#include "SandboxPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HealthComponent.h"
#include "QuestComponent.h"
#include "SandboxWeaponBase.h"

ASandboxPlayerCharacter::ASandboxPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponClass = nullptr;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(SpringArm);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	QuestComponent = CreateDefaultSubobject<UQuestComponent>(TEXT("QuestComponent"));

	TargetFOV = 90.0f;
	TargetArmLength = 300.0f;
}

void ASandboxPlayerCharacter::StartFire()
{
	if (CurrentWeapon) CurrentWeapon->Fire();
}

void ASandboxPlayerCharacter::OnStartAiming()
{
	if (CurrentWeapon) CurrentWeapon->SetAiming(true);
	TargetFOV = 60.0f;
	TargetArmLength = 100.f;
}

void ASandboxPlayerCharacter::OnStopAiming()
{
	if (CurrentWeapon) CurrentWeapon->SetAiming(false);
	TargetFOV = 90.0f;
	TargetArmLength = 300.f;
}

void ASandboxPlayerCharacter::HandleDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Dead"));
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC) DisableInput(PC);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
}

void ASandboxPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HealthComponent)
	{
		HealthComponent->OnHealthDead.AddDynamic(this, &ASandboxPlayerCharacter::HandleDeath);
	}

	if (WeaponClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		CurrentWeapon = GetWorld()->SpawnActor<ASandboxWeaponBase>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

		if (CurrentWeapon)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
			CurrentWeapon->AttachToComponent(GetMesh(), AttachmentRules, FName("weapon_r_muzzle"));
		}
	}
}

void ASandboxPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (FollowCamera)
	{
		float CurrentFOV = FollowCamera->FieldOfView;
		FollowCamera->SetFieldOfView(FMath::FInterpTo(CurrentFOV, TargetFOV, DeltaTime, 10.0f));
	}
	if (SpringArm)
	{
		float CurrentArmLength = SpringArm->TargetArmLength;
		SpringArm->TargetArmLength = FMath::FInterpTo(CurrentArmLength, TargetArmLength, DeltaTime, 10.0f);
	}
}

void ASandboxPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
