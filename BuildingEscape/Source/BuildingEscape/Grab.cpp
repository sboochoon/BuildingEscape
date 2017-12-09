// Shaad Boochoon 2017

#include "Grab.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UGrab::UGrab()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrab::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();

	SetupInputComponent();
	
}

void UGrab::FindPhysicsHandleComponent()
{
	//Look for attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s PhysicsHandle Component Missing From Actor"), *GetOwner()->GetName());
	}
}

void UGrab::SetupInputComponent()
{
	//Look for attached Input Component
	PawnInput = GetOwner()->FindComponentByClass<UInputComponent>();
	if (PawnInput)
	{
		//Bind Grab() and Release() to the input
		PawnInput->BindAction("Grab", IE_Pressed, this, &UGrab::Grab);
		PawnInput->BindAction("Grab", IE_Released, this, &UGrab::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s Input Component Missing From Actor"), *GetOwner()->GetName());
	}
}

void UGrab::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"));

	//Try and reach any actors with physics body collision channel set
	auto GetHitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = GetHitResult.GetComponent();
	//If we hit somethin then attach a physics handle
	ActorHit = GetHitResult.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor Hit: %s"), *ActorHit->GetName());
		PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
	}
}

void UGrab::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"));

	//TODO release physics handle
	PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrab::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//get the player viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewpointLocation, OUT PlayerViewpointRotation);

	//Draw a red trace in the world to visualize
	LineTraceEnd = PlayerViewpointLocation + (PlayerViewpointRotation.Vector()*Reach);

	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
	// ...
}

const FHitResult UGrab::GetFirstPhysicsBodyInReach()
{
	//get the player viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewpointLocation, OUT PlayerViewpointRotation);

	//Draw a red trace in the world to visualize
	LineTraceEnd = PlayerViewpointLocation + (PlayerViewpointRotation.Vector()*Reach);

	//raycast to reach distance
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewpointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	//see what we hit
	return Hit;
}

