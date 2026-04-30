// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::PerformAsyncTrace(FVector Start, FVector End)
{
    UWorld* World = GetWorld();
    if (!World) return;

    FTraceDelegate TraceDelegate;


    TraceDelegate.BindLambda([this](const FTraceHandle& Handle, FTraceDatum& Data) {
        this->OnTraceCompleted(Handle, Data);
        });

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    World->AsyncLineTraceByChannel(
        EAsyncTraceType::Single,
        Start, End,
        ECC_Camera,
        Params,
        FCollisionResponseParams::DefaultResponseParam,
        &TraceDelegate
    );

    DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.0f, 0);
}

void AEnemy::OnTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data)
{
    if (Data.OutHits.Num() > 0)
    {
        AActor* HitActor = Data.OutHits[0].GetActor();

        // HitActor È®ÀÎ
        if (HitActor)
        {
            UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *HitActor->GetName());

            
            OnPlayerDetected(HitActor);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Trace finished: Hit Nothing!"));
    }
}