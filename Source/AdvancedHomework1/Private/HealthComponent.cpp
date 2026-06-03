#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	MaxHealth = 100.0f;
	CurrentHealth = 100.0f;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void UHealthComponent::TakeDamage(float DamageAmount, AActor* DamageCauser)
{
	if (IsDead()) return;

	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
	OnHealthDamaged.Broadcast(CurrentHealth, MaxHealth);

	if (IsDead())
	{
		OnHealthDead.Broadcast();
		OnHealthDeadWithInstigator.Broadcast(DamageCauser);
	}
}
