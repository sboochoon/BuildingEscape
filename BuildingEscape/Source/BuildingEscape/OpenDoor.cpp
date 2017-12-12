// Shaad Boochoon 2017

#include "OpenDoor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	//Get this door
	Owner = GetOwner();

	//Door does not have a PressurePlate object assigned
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing PressurePlate"), *Owner->GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*float testMass = GetTotalMassOfActorsOnPlate();
	UE_LOG(LogTemp, Warning, TEXT("Mass in volume: %f "), testMass);*/


	//Poll the trigger volume to see if the mass inside is enough, if it is then open the door, else close it
	if (GetTotalMassOfActorsOnPlate() >= MassToTriggerDoorOpen)
	{
		OnOpenRequest.Broadcast();
	}
	else
	{
		OnCloseRequest.Broadcast();
	}
}

///Return total mass of actors that have overlap events checked
float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	//Find all overlapping actors
	if (!PressurePlate) { return TotalMass; }

	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	//Iterate through them adding their masses
	for (const auto& Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

