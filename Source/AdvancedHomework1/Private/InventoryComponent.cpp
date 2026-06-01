// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UInventoryComponent::RegisterItem(const FItemData& NewItemInfo)
{
    // ItemID를 Key로 하여 정보를 저장하거나 갱신.
    ItemMap.Add(NewItemInfo.ItemID, NewItemInfo);

    UE_LOG(LogTemp, Log, TEXT("마스터 DB 등록 완료: [%d] %s"), NewItemInfo.ItemID, *NewItemInfo.Name);
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

    // 테스트용 아이템 생성
    FItemData TestItem;
    TestItem.ItemID = 1;
    TestItem.Name = TEXT("전설의 물약");
    TestItem.Description = TEXT("10초를 버틴 자만 사용할 수 있는 물약입니다.");
    TestItem.Count = 1;
    TestItem.RequiredTitle = TEXT("10SecPlay"); // 타이머로 얻을 칭호와 일치시킴

    RegisterItem(TestItem);
    // 만든 아이템을 인벤토리에 추가
    AddItemByID(1, 1);
    // 10초 후 칭호 추가
    GetWorld()->GetTimerManager().SetTimer(TitleTimerHandle, [this]() {AddTitle("10SecPlay"); }, 10.0f, false);
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UInventoryComponent::AddItemByID(int32 ItemID, int32 Amount)
{
    // 1. TMap에서 정보가 있는지 먼저 확인
    if (!ItemMap.Contains(ItemID)) return;

    // 2. TArray에 이미 있는지 확인 (순차 검색)
    bool bAlreadyHas = false;
    for (FItemData& Slot : Inventory)
    {
        if (Slot.ItemID == ItemID)
        {
            Slot.Count += Amount; // 수량 업데이트
            ItemMap[ItemID].Count = Slot.Count; // TMap과 동기화
            bAlreadyHas = true;
            break;
        }
    }

    // 3. 가방에 없는 새 아이템이면 TMap 정보를 복사해서 가방에 추가
    if (!bAlreadyHas)
    {
        FItemData NewItem = ItemMap[ItemID];
        NewItem.Count = Amount;
        Inventory.Add(NewItem);
    }

    OnInventoryUpdated.Broadcast(); // UI에 알림
}

bool UInventoryComponent::UseItem(int32 ItemID)
{
    // ItemMap에 해당 ID가 있는지 확인
    if (!ItemMap.Contains(ItemID))
    {
        UE_LOG(LogTemp, Error, TEXT("아이템을 찾을 수 없습니다. ID: %d"), ItemID);
        return false;
    }

    // 레퍼런스로 가져와서 원본 데이터 수정 가능하게 함
    FItemData& Item = ItemMap[ItemID];

    // 3. 칭호 체크: RequiredTitle이 비어있지 않은데 획득한 Titles에 없다면 거부
    if (!Item.RequiredTitle.IsEmpty() && !Titles.Contains(Item.RequiredTitle))
    {
        UE_LOG(LogTemp, Warning, TEXT("사용 불가: '%s' 칭호가 필요합니다."), *Item.RequiredTitle);
        return false;
    }

    // 4. 수량 체크 및 감소
    if (Item.Count > 0)
    {
        Item.Count--;

        // TArray(Inventory) 동기화 및 필요 시 삭제
        for (int32 i = 0; i < Inventory.Num(); i++)
        {
            if (Inventory[i].ItemID == ItemID)
            {
                if (Item.Count <= 0)
                {
                    Inventory.RemoveAt(i);
                }
                else
                {
                    Inventory[i].Count = Item.Count;
                }
                break;
            }
        }

        UE_LOG(LogTemp, Warning, TEXT("%s 아이템 사용! 남은 수량: %d"), *Item.Name, Item.Count);
        OnInventoryUpdated.Broadcast();
        return true;
    }

    return false;
}

void UInventoryComponent::AddTitle(const FString& Title)
{
	Titles.Add(Title);
    UE_LOG(LogTemp, Warning, TEXT("새로운 칭호 획득: %s"), *Title);
}

FItemData UInventoryComponent::GetItemInfo(int32 ItemID)
{
    // TMap의 Contains를 사용해 Key가 존재하는지 먼저 확인
    if (ItemMap.Contains(ItemID))
    {
        UE_LOG(LogTemp, Warning, TEXT("아이템 검색 성공: %s"), *ItemMap[ItemID].Name);
        return ItemMap[ItemID];
    }

    UE_LOG(LogTemp, Error, TEXT("ID %d번에 해당하는 아이템 정보가 없습니다."), ItemID);

    // 찾지 못했을 경우 빈 구조체 반환
    return FItemData();
}
