#pragma once

#include "CoreMinimal.h"
#include "Characters/C_Unit.h"
#include <queue>
#include "Enums/C_CastingElement.h"
#include "Enums/C_Direction.h"
#include "C_Mage.generated.h"

using namespace std;

/**
 *
 */
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class UWidgetComponent;

struct FInputActionInstance;

class UC_DamageComponent;
class UC_MagicDispenser;
class UC_DashEffectComponent;

//-------------------------------[struct FCastingStack]-------------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FCastingStack
{
	GENERATED_USTRUCT_BODY()

public:
	FCastingStack()
	{
		UnsortedCastingStack.SetNum(5);
		CastingLog.SetNum(5);
		SortedCastingStack;
		InputedElement = ECastingElement::None;
		StackIndex = 0;
		bOnCasting = false;
	}
	///////////////////////////////////////////////////////////
	// Code: void BeginCasting()
	// Desc: Begin to cast element and return able to insert
	///////////////////////////////////////////////////////////
	bool BeginCasting(ECastingElement Element)
	{
		InputedElement = Element;

		if (CheckInserting() == false)
		{
			BreakCasting();
			return false;
		}
		else
		{
			InsertElement();
		}

		return true;
	}

	///////////////////////////////////////////////////////////
	// Code: void EndCasting()
	// Desc: End casting
	///////////////////////////////////////////////////////////
	void EndCasting()
	{
		ClearCastingStack();
	}

	///////////////////////////////////////////////////////////
	// Code: void GetUnsortedCastingStack(OUT vector<ECastingElement>* UICasctingStack)
	// Desc: Substitute stacked element values to UICasingStack
	///////////////////////////////////////////////////////////
	void GetUnsortedCastingStack(OUT TArray<ECastingElement>* UICastingStack) { *UICastingStack = UnsortedCastingStack; }

	const int32 StackSize() { return SortedCastingStack.size(); }
	const bool& OnCasting() { return bOnCasting; }
	const bool IsCasting() { return SortedCastingStack.size() > 0; }

private:
	///////////////////////////////////////////////////////////
	// Code: void BreakCasting()
	// Desc: When get damage while casting, apeared breaking casting
	///////////////////////////////////////////////////////////
	void BreakCasting()
	{
		ClearCastingStack();
	}

	///////////////////////////////////////////////////////////
	// Code: void InsertElement()
	// Desc: Insert element data to stacks
	///////////////////////////////////////////////////////////
	void InsertElement()
	{
		if (SortedCastingStack.size() >= 5)
		{
			// Msg "I can't stack anymore"
			return;
		}

		int32 ElementNum = CAST(int32, InputedElement);

		SortedCastingStack.push(ElementNum);
		UnsortedCastingStack[StackIndex] = InputedElement;
		CastingLog[ElementNum]++;

		StackIndex++;
	}

	///////////////////////////////////////////////////////////
	// Code: void ClearCastingStack()
	// Desc: Clear Casting stacks
	///////////////////////////////////////////////////////////
	void ClearCastingStack()
	{
		int32 iter = SortedCastingStack.size();

		for (int i = 0; i < iter; i++)
		{
			SortedCastingStack.pop();
			UnsortedCastingStack[i] = ECastingElement::None;
		}

		for (int i = 1; i < CastingLog.Num(); i++)
			CastingLog[i] = 0;

		StackIndex = 0;
		InputedElement = ECastingElement::None;
		bOnCasting = false;
	}

	///////////////////////////////////////////////////////////
	// Code: void CheckInserting()
	// Desc: Check to be able inserting current inputed element
	///////////////////////////////////////////////////////////
	bool CheckInserting()
	{
		if (StackIndex == 5) return false;

		switch (InputedElement)
		{
		case ECastingElement::Fire:
			if (CastingLog[CAST(int32, ECastingElement::Ice)] > 0)
				return false;
			break;

		case ECastingElement::Ice:
			if (CastingLog[CAST(int32, ECastingElement::Fire)] > 0)
				return false;
			break;

		case ECastingElement::Light:
			if (CastingLog[CAST(int32, ECastingElement::Dark)] > 0)
				return false;
			break;

		case ECastingElement::Dark:
			if (CastingLog[CAST(int32, ECastingElement::Light)] > 0)
				return false;
			break;
		}

		return true;
	}

private:
	priority_queue<int32> SortedCastingStack;
	TArray<ECastingElement> UnsortedCastingStack;
	TArray<int32> CastingLog;

	ECastingElement InputedElement;
	int32 StackIndex = 0;
	
	bool bOnCasting = false;
};

//-------------------------------[class AC_Mage]-------------------------------------------------------------------------------------------------------------------
UCLASS()
class FIVECIRCLEMAGE_API AC_Mage : public AC_Unit
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USpringArmComponent* CameraArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UWidgetComponent* WidgetComp;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UWidgetComponent* CastingStackUIComp;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UC_MagicDispenser* Dispenser;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UC_DashEffectComponent* DashEffectComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<FString, UInputAction*> InputActions;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		float DashCoolTime = 2.0f;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	class UNiagaraSystem* TestNiagara;
	//
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	class UNiagaraComponent* TestComp;

protected:
	UFUNCTION()
		void EndDash();

	UFUNCTION()
		void EndDashCoolTime();

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
	virtual void GetDmg(const float Dmg, const EUnitState Type) override;

	EDirectionState GetDirectionState() { return DirectionState; }

	void ResetCastingBreak() { bCastingBreak = false; }
	void ResetCasting() { bCasting = false; }
	void ResetOnFire() { bOnFire = false; }

	const bool IsDash() { return bDash; }
	const bool IsCasting() const { return bCasting; }
	const bool IsCastingBreak() const { return bCastingBreak; }
	const bool IsOnFire() const { return bOnFire; }
	const bool IsAlive() const { return bAlive; }

	void SetMouseLocation(const FVector Value) { MouseLocation = Value; }
	const FVector GetLookDirection() const { return LookDirection; }

	void PushCastingStack(const ECastingElement Element);

	virtual void OnDeath();

	void CameraSetting();

protected:
	///////////////////////////////////////////////////////////////////////////
	// Bind Action Function
	///////////////////////////////////////////////////////////////////////////
	void OnDash();
	void OnMagicCast();
	///////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	// Bind Axis Function
	///////////////////////////////////////////////////////////////////////////
	void ForwardMove(const FInputActionInstance& Instance);
	void RightMove(const FInputActionInstance& Instance);
	///////////////////////////////////////////////////////////////////////////`

	///////////////////////////////////////////////////////////////////////////
	// Casting Magic Skill Func
	///////////////////////////////////////////////////////////////////////////
	void GetCastingStack(OUT TArray<ECastingElement>* UICastingStack);
	///////////////////////////////////////////////////////////////////////////

private:
	void AddInputAction(FString Key, FString Path);

private:
	FCastingStack CastingStack;
	EDirectionState DirectionState = EDirectionState::Forward;

	bool bDash = false;
	bool bDashCoolTime = false;
	bool bCasting = false;
	bool bCastingBreak = false;
	bool bOnFire = false;
	bool bAlive = false;

	// Delay between each stacking casting element
	bool bEnablePushElement = true;
	float CurCastingDelayTime = 0.0f;
	const TArray<float> CastingDelay = { 0.5f, 0.7f, 1.0f, 1.3f, 1.5f };
	ECastingElement PushedElement;

	/**
	* Traced mouse position
	*/
	FVector MouseLocation = FVector::ZeroVector;
	FVector LookDirection = FVector::ZeroVector;

	FTimerDelegate DashDelegate;
	FTimerDelegate DashCoolTimeDelegate;
};
