// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterListItem.h"
#include "../Global/CGameInstance.h"
#include "../Global/CBlueprintFunctionLibrary.h"
#include "../Packets/ClientPackets/Packets.h"

void UCharacterListItem::SelectCharacter()
{
	UE_LOG(LogTemp, Log, TEXT("Select Character"));
	UE_LOG(LogTemp, Log, TEXT("Nick Name: %s"), *NickName);

	// 캐릭터 선택 패킷 전달
	UCGameInstance* Inst = Cast<UCGameInstance>(GetGameInstance());

	std::string nickNameUTF8;
	UCBlueprintFunctionLibrary::FStringToUTF8(NickName, nickNameUTF8);

	SelectCharacterPacket packet;
	packet.SelectCharNickName = nickNameUTF8;

	//ServerSerializer sr;
	//packet >> sr;

	//if (false != Inst->SendBytes(sr.GetBuffer()))
	//{
	//	int a = 0;
	//}

	UE_LOG(LogTemp, Log, TEXT("Test Server Packet"));
	std::shared_ptr<SelectCharacterResultPacket> serverPacket = std::make_shared<SelectCharacterResultPacket>();
	serverPacket->ResultCode = EResultCode::OK;
	serverPacket->SelectCharNickName = nickNameUTF8;
	Inst->AddServerPacket(serverPacket);
}
