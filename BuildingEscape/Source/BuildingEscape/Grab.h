// Shaad Boochoon 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DrawDebugHelpers.h"
#include "Grab.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrab : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrab();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	//Raycast and grab what's in reach
	void Grab();

	void FindPhysicsHandleComponent();
	void SetupInputComponent();

	//Release what is grabbed
	void Release();

	// Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	//Returns current end of Reach line
	FVector GetReachLineEnd();

	float Reach = 100.f;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* PawnInput = nullptr;
	FHitResult Hit;
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;
	AActor* ActorHit = nullptr;
};
