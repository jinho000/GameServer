#include "CharacterListPacketHandler.h"
#include <Kismet/GameplayStatics.h>
#include "../../Global/CGameInstance.h"


void CharacterListPacketHandler::Start()
{
	UE_LOG(LogTemp, Log, TEXT("CharacterListPacketHandler"));

	// 유저의 캐릭터 정보 저장
	UE_LOG(LogTemp, Log, TEXT("Save User Character List to GameInstance"));
	const std::vector<FCharacterInfo>& characterList = m_packet->CharacterList;
	
	for (int i = 0; i < characterList.size(); ++i)
	{
		m_pGameInst->UserCharacterList.push_back(characterList[i]);
	}

	UE_LOG(LogTemp, Log, TEXT("Open CharacterSelect Level"));
	UGameplayStatics::OpenLevel(m_pWorld, TEXT("CharacterSelect"));
}
