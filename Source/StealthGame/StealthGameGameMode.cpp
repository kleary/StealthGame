// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "StealthGameGameMode.h"
#include "StealthGameHUD.h"
#include "StealthGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AStealthGameGameMode::AStealthGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AStealthGameHUD::StaticClass();
}

void AStealthGameGameMode::CompleteMission(APawn* InstigatorPawn) {

	if (InstigatorPawn) {
		InstigatorPawn->DisableInput(nullptr);

		if (SpectatorViewpointClass) {
			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatorViewpointClass, ReturnedActors);

			if (ReturnedActors.Num() > 0) {
				AActor* NewViewTarget = ReturnedActors[0];
				APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
				if (PC) {
					PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		} else {
			UE_LOG(LogTemp, Warning, TEXT("SpectatorViewpointClass is nullptr. Please update GameMode with valid viewpoint class."));
		}

	}

	OnMissionCompleted(InstigatorPawn);

}

