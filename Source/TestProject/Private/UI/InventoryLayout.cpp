// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryLayout.h"
#include "UI/SlotLayout.h"
#include "Components/UniformGridPanel.h"
#include "MyPlayerController.h"

DECLARE_LOG_CATEGORY_EXTERN(LogInventory, Verbose, Verbose)

UInventoryLayout::UInventoryLayout()
{
	static ConstructorHelpers::FClassFinder<USlotLayout> InventorySlotObj(TEXT("/Game/UI/WBP_SlotLayout.WBP_SlotLayout_C"));
	WidgetClassInventorySlot = InventorySlotObj.Class;

	static ConstructorHelpers::FObjectFinder<UTexture2D> ObjectFind(TEXT("/Game/Textures/T_UI_Slot"));
	Background_Slot = ObjectFind.Object;
	
	/*static ConstructorHelpers::FObjectFinder<UTexture2D> ObjectItemBorder(TEXT("/Game/Textures/T_UI_Item_Border"));
	DefaultBorder = ObjectItemBorder.Object;*/
}

void UInventoryLayout::NativeConstruct()
{
	Super::NativeConstruct();

	Super::SetTitleToWindow("INVENTORY");
 
	InitializeInventorySlots();
}

void UInventoryLayout::InitializeInventorySlots()
{
	uint8 InventoryIndex = 0;
	for(int i = 0; i < 7; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			W_InventorySlot = CreateWidget<USlotLayout>(GetWorld(), WidgetClassInventorySlot);
			InventoryGridPanel->AddChildToUniformGrid(W_InventorySlot, i, j);

			W_InventorySlot->InitializeSlot(Background_Slot, GetOwningPlayer());
			W_InventorySlot->InventorySlotIndex = InventoryIndex;
			
			InventorySlotsArray.Add(W_InventorySlot);

			InventoryIndex++;
		}
	}
}

void UInventoryLayout::RefreshInventorySlots()
{
	const uint8 InventoryLimit = PlayerController->InventoryComponent->NumberOfSlots;

	FSlotStructure CurrentSlot = {};
	for(int i = 0; i < InventoryLimit; i++)
	{
		CurrentSlot = PlayerController->InventoryComponent->Inventory[i];

		/* Update Empty Slot */
		if(CurrentSlot.Amount <= 0){
			CurrentSlot = PlayerController->InventoryComponent->GetEmptySlot();
		}
		
		InventorySlotsArray[i]->UpdateSlot(CurrentSlot);
	}
}

void UInventoryLayout::OnButtonQuitClicked()
{
	if (IsValid(PlayerController))
	{
		PlayerController->ToggleInventory();
	}
}