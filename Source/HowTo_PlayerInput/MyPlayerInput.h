// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPlayerInput.generated.h"

UCLASS()
class HOWTO_PLAYERINPUT_API AMyPlayerInput : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPlayerInput();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;

	// input functions
	void Move_XAxis(float fAxisValue);
	void Move_YAxis(float fAxisValue);
	void StartGrowing();
	void StopGrowing();

	// input variables
	FVector CurrentVelocity;
	bool bGrowing;

};
