// Fill out your copyright notice in the Description page of Project Settings.

#include "BlackHole.h"
#include "Components/SphereComponent.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = StaticMesh;

	EventHorizon = CreateDefaultSubobject<USphereComponent>(TEXT("EventHorizon"));
	EventHorizon->SetSphereRadius(100);
	EventHorizon->SetupAttachment(StaticMesh);
	EventHorizon->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	EventHorizon->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);


	AreaOfEffect = CreateDefaultSubobject<USphereComponent>(TEXT("AreaOfEffect"));
	AreaOfEffect->SetSphereRadius(3000);
	AreaOfEffect->SetupAttachment(StaticMesh);
	AreaOfEffect->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	AreaOfEffect->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{

	Super::BeginPlay();
	EventHorizon->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapEventHorizon);
	
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlappingComponents;
	AreaOfEffect->GetOverlappingComponents(OverlappingComponents);
	for (int32 i = 0; i < OverlappingComponents.Num(); i++) {
		UPrimitiveComponent* PrimComp = OverlappingComponents[i];
		if (PrimComp && PrimComp->IsSimulatingPhysics()) {
			const float SphereRadius = AreaOfEffect->GetScaledSphereRadius();

			PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, GravityForce, ERadialImpulseFalloff::RIF_Constant, true);
			
		}
	}

}

void ABlackHole::OverlapEventHorizon(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor) {
		OtherActor->Destroy();
	}
}

