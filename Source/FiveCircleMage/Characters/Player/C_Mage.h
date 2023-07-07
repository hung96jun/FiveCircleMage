#pragma once

#include "CoreMinimal.h"
#include "Characters/C_Unit.h"
#include "Enums/C_Direction.h"
#include "C_Mage.generated.h"

/**
 * 
 */
class UInputAction;
class UCameraComponent;
class USpringArmComponent;

struct FInputActionInstance;

USTRUCT(BlueprintType)
struct FUnitDirection
{
	GENERATED_USTRUCT_BODY()

public:
	FVector ForwardVector;
	FVector RightVector;
};

UCLASS()
class FIVECIRCLEMAGE_API AC_Mage : public AC_Unit
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USpringArmComponent* CameraArm;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<FString, UInputAction*> InputActions;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		FUnitDirection UnitDirection;

private:
	const FVector FORWARD = FVector(1.0f, 0.0f, 0.0f);
	const FVector RIGHT = FVector(0.0f, 1.0f, 0.0f);

public:
	AC_Mage();

protected:
	virtual void BeginPlay() final;

public:
	virtual void Tick(float DeltaTime) final;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) final;

	EDirectionState GetDirectionState() { return DirectionState; }

	bool GetIsDash() { return IsDash; }

	void EndDash() { IsDash = false; }

protected:
	///////////////////////////////////////////////////////////////////////////
	// Bind Action Function
	///////////////////////////////////////////////////////////////////////////
	void OnDash();
	void OnMagicCast();
	void OnAssembleElement();
	///////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	// Bind Axis Function
	///////////////////////////////////////////////////////////////////////////
	void ForwardMove(const FInputActionInstance& Instance);
	void RightMove(const FInputActionInstance& Instance);
	///////////////////////////////////////////////////////////////////////////
private:
	void AddInputAction(FString Key, FString Path);

private:
	EDirectionState DirectionState = EDirectionState::Forward;

	bool IsDash = false;
};
