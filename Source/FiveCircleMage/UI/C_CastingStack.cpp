// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_CastingStack.h"
#include "Components/Image.h"

UC_CastingStack::UC_CastingStack(const FObjectInitializer& ObjectInitializer)
	:UUserWidget(ObjectInitializer)
{
	ElementRefs[0] = "/Script/Engine.Texture2D'/Game/Assets/UI/CastingStack/null.null'";
	ElementRefs[1] = "/Script/Engine.Texture2D'/Game/Assets/UI/CastingStack/fire.fire'";
	ElementRefs[2] = "/Script/Engine.Texture2D'/Game/Assets/UI/CastingStack/ice.ice'";
	ElementRefs[3] = "/Script/Engine.Texture2D'/Game/Assets/UI/CastingStack/light.light'";
	ElementRefs[4] = "/Script/Engine.Texture2D'/Game/Assets/UI/CastingStack/dark.dark'";
}

void UC_CastingStack::ShowPanel()
{
	if (bIsActive == true) return;

	bIsActive = true;

	InitStack();
}

void UC_CastingStack::ShakePanel()
{
	Images[0]->GetRenderTransform();
}

void UC_CastingStack::HidePanel()
{
	bIsActive = false;

	for (UImage* image : Images)
		image->SetVisibility(ESlateVisibility::Hidden);

	for (UImage* image : FXs)
		image->SetOpacity(0.0f);
}

void UC_CastingStack::SetStackSlot(int32 SlotNum, int32 ElementNum, float DelayTime)
{
	UTexture2D* texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *ElementRefs[ElementNum]));
	Images[SlotNum]->SetBrushFromTexture(texture);

	if (DelayTime <= 0.0f) return;

	SetImageTransformX(SlotNum);

	TargetCastingTime = DelayTime;
	CurCastingTime = 0.0f;
	CurSlotNum = SlotNum;
}

void UC_CastingStack::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UC_CastingStack::NativeConstruct()
{
	Super::NativeConstruct();

	Images.Push(CStack_0);
	Images.Push(CStack_1);
	Images.Push(CStack_2);
	Images.Push(CStack_3);
	Images.Push(CStack_4);

	FXs.Push(FX_0);
	FXs.Push(FX_1);
	FXs.Push(FX_2);
	FXs.Push(FX_3);
	FXs.Push(FX_4);

	InitStack();
}

void UC_CastingStack::NativeDestruct()
{
	Super::NativeDestruct();
}

void UC_CastingStack::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (bIsActive == false) return;

	Super::NativeTick(MyGeometry, InDeltaTime);

	if (CurCastingTime < TargetCastingTime)
	{
		CurCastingTime += InDeltaTime;
		
		FXs[CurSlotNum]->SetOpacity(1 - (CurCastingTime / TargetCastingTime));

		if (CurCastingTime >= TargetCastingTime)
		{
			OpeningOpacity = 1.0f;
			FXs[CurSlotNum]->SetColorAndOpacity(FLinearColor(1, 1, 1, OpeningOpacity));
			CurOpeningSlotNum = CurSlotNum;
			IsSlotOpening = true;
		}
	}

	if (IsSlotOpening)
	{
		OpeningOpacity -= InDeltaTime * 2.0f;
		FXs[CurOpeningSlotNum]->SetOpacity(OpeningOpacity);

		if (OpeningOpacity <= 0.0f)
			IsSlotOpening = false;
	}
}

void UC_CastingStack::InitStack()
{
	for (int32 idx = 0; idx < Images.Num(); idx++)
	{
		SetStackSlot(idx, 0);
		Images[idx]->SetVisibility(ESlateVisibility::Visible);

		FXs[idx]->SetColorAndOpacity(FLinearColor::Transparent);
	}
}

void UC_CastingStack::SetImageTransformX(int32 SlotNum)
{
	FWidgetTransform transform = Images[SlotNum]->GetRenderTransform();
	transform.Translation.X = 80 - (SlotNum * 24);

	for (int32 idx = 0; idx <= SlotNum; idx++)
	{
		Images[idx]->SetRenderTransform(transform);
		FXs[idx]->SetRenderTransform(transform);
	}
}