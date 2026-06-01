// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentHealth = MaxHealth;
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
