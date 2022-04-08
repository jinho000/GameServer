#include "ChatMessagePacketHandler.h"
#include <Kismet/GameplayStatics.h>
#include "../../Play/Chat/CChatMessage.h"
#include "../../Global/CGameInstance.h"
#include "../../Play/Chat/CChatWindow.h"

void ChatMessagePacketHandler::Start()
{
	UE_LOG(LogTemp, Log, TEXT("ChatMessagePacketHandler"));

	// 패킷 분석
	FString nickName = FUTF8ToTCHAR(m_packet->NickName.c_str()).Get();
	FString message = FUTF8ToTCHAR(m_packet->Message.c_str()).Get();

	// 채팅 오브젝트 
	UCChatMessage* chatMessage = NewObject<UCChatMessage>();
	chatMessage->Init(nickName, message);

	// 채팅윈도우에 채팅전달
	UCChatWindow* pChatWindow = m_pGameInst->GetChatWindow();
	pChatWindow->AddChatMessage(chatMessage);

	UE_LOG(LogTemp, Log, TEXT("Recv NickName: %s"), *nickName);
	UE_LOG(LogTemp, Log, TEXT("Recv Message: %s"), *message);
}

