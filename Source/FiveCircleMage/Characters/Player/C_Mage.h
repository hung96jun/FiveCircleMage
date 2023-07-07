#pragma once

#include "CoreMinimal.h"
#include "Characters/C_Unit.h"
#include <queue>
#include "Enums/C_CastingElement.h"
#include "UI/C_ElementPanel.h"

#include "C_Mage.generated.h"

using namespace std;

/**
 * 
 */
class UInputAction;
class UCameraComponent;
class USpringArmComponent;

struct FInputActionInstance;

class UC_DamageComponent;

USTRUCT(BlueprintType)
struct FUnitDirection
{
	GENERATED_USTRUCT_BODY()

public:
	FVector ForwardVector;
	FVector RightVector;
};

//-------------------------------[struct FCastingStack]-------------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FCastingStack
{
	GENERATED_USTRUCT_BODY()

public:
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
	void GetUnsortedCastingStack(OUT vector<ECastingElement>* UICastingStack) { *UICastingStack = UnsortedCastingStack; }

	const bool& OnCasting() { return bOnCasting; }

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

		for (int i = 1; i < CastingLog.size(); i++)
			CastingLog[i] = 0;

		StackIndex = 0;
		InputedElement = ECastingElement::None;
	}

	///////////////////////////////////////////////////////////
	// Code: void CheckInserting()
	// Desc: Check to be able inserting current inputed element
	///////////////////////////////////////////////////////////
	bool CheckInserting()
	{
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
			if (CastingLog[CAST(int32, ECastingElement::Ice)] > 0)
				return false;
			break;
		}

		return true;
	}

private:
	priority_queue<int32> SortedCastingStack;
	vector<ECastingElement> UnsortedCastingStack;
	vector<int32> CastingLog;

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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<FString, UInputAction*> InputActions;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		FUnitDirection UnitDirection;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UC_DamageComponent* DamageComponent;

	//------------------------------------------------------------------
	/*UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UUserWidget* ElementPanel;*/
	//------------------------------------------------------------------

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

	///////////////////////////////////////////////////////////////////////////
	// Casting Magic Skill Func
	///////////////////////////////////////////////////////////////////////////
	void OnElementPanel(const FInputActionInstance& Instance);
	void OpenElementPanel();
	void CloseElementPanel();

	void GetCastingStack(OUT vector<ECastingElement>* UICastingStack);
	void Casting();
	///////////////////////////////////////////////////////////////////////////

private:
	void AddInputAction(FString Key, FString Path);

private:
	FCastingStack CastingStack;
};
