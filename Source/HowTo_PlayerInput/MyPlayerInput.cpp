// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerInput.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyPlayerInput::AMyPlayerInput()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// set this pawn to be controlled by the lowest numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// create dummy root component to attach things to
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// create a camera and a visible object
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	// attach our camera and visible object to root component
	OurCamera->SetupAttachment(RootComponent);

	// Offset and rotate camera
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyPlayerInput::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPlayerInput::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// handle growing and shrinking
	{
		float CurrentScale = OurVisibleComponent->GetComponentScale().X;
		if (bGrowing)
		{
			// grow to target size in one second
			CurrentScale += DeltaTime;
		}
		else {
			// shrink half as fast as it grows
			CurrentScale -= (DeltaTime * 0.5f);
		}

		// make sure we never drop below starting size or increase past target size
		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
		OurVisibleComponent->SetWorldScale3D((FVector(CurrentScale)));
	}

	// handle movement 
	{
		if (!CurrentVelocity.IsZero())
		{
			FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
			SetActorLocation(NewLocation);
		}
	}
}

// Called to bind functionality to input
void AMyPlayerInput::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// respond when "grow" key is pressed or released
	InputComponent->BindAction("Grow", IE_Pressed, this, &AMyPlayerInput::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &AMyPlayerInput::StopGrowing);

	// respond every frame to the values of our two movement axes
	InputComponent->BindAxis("MoveX", this, &AMyPlayerInput::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AMyPlayerInput::Move_YAxis);
}

void AMyPlayerInput::Move_XAxis(float fAxisValue) {
	// move 100 units per second forward or backwards
	CurrentVelocity.X = FMath::Clamp(fAxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPlayerInput::Move_YAxis(float fAxisValue) {
	// move 100 units per second forward or backwards
	CurrentVelocity.Y = FMath::Clamp(fAxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPlayerInput::StartGrowing() {
	bGrowing = true;
}

void AMyPlayerInput::StopGrowing() {
	bGrowing = false;
}
