// Shaad Boochoon 2017

#include "Grab.h"
#include "Engine/World.h"

#define OUT
// Sets default values for this component's properties
UGrab::UGrab()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrab::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrab::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//get the player viewpoint
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewpointLocation, OUT PlayerViewpointRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Player position: %s, Player rotation: %s"), *PlayerViewpointLocation.ToString(), *PlayerViewpointRotation.ToString());

	//Draw a red trace in the world to visualize
	FVector LineTraceEnd = PlayerViewpointLocation + (PlayerViewpointRotation.Vector()*Reach);
	DrawDebugLine(GetWorld(), PlayerViewpointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 2.f);

	//raycast to reach distance
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewpointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
	//	UE_LOG(LogTemp, Warning, TEXT("Actor Hit: %s"), *ActorHit->GetName());
	}

	//see what we hit

	// ...
}

