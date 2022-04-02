#include "CharacterListPacketHandler.h"
#include <Kismet/GameplayStatics.h>
#include "../../Global/CGameInstance.h"


CharacterListPacketHandler::CharacterListPacketHandler(const std::shared_ptr<CharacterListPacket>& _packet)
	: m_packet(_packet)
{
}

CharacterListPacketHandler::~CharacterListPacketHandler()
{
}

void CharacterListPacketHandler::Start()
{
	UE_LOG(LogTemp, Log, TEXT("CharacterListPacketHandler"));

	// ������ ĳ���� ���� ����
	UE_LOG(LogTemp, Log, TEXT("Save User Character List to GameInstance"));
	const std::vector<FCharacterInfo>& characterList = m_packet->CharacterList;
	
	for (int i = 0; i < characterList.size(); ++i)
	{
		m_pGameInst->UserCharacterList.push_back(characterList[i]);
	}

	UE_LOG(LogTemp, Log, TEXT("Open CharacterSelect Level"));
	UGameplayStatics::OpenLevel(m_pWorld, TEXT("CharacterSelect"));
}
