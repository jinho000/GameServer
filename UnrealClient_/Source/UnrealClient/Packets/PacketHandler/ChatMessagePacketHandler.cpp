#include "ChatMessagePacketHandler.h"
#include <Kismet/GameplayStatics.h>
#include "../../Play/Chat/CChatMessage.h"
#include "../../Global/CGameInstance.h"
#include "../../Play/Chat/CChatWindow.h"

ChatMessagePacketHandler::ChatMessagePacketHandler(const std::shared_ptr<ChatMessagePacket>& _packet)
	: m_packet(_packet)
{
}

ChatMessagePacketHandler::~ChatMessagePacketHandler()
{
}

void ChatMessagePacketHandler::Start()
{
	// 패킷 분석
	FString userID = FUTF8ToTCHAR(m_packet->m_userID.c_str()).Get();
	FString message = FUTF8ToTCHAR(m_packet->m_chatMessage.c_str()).Get();

	// 채팅 오브젝트 
	UCChatMessage* chatMessage = NewObject<UCChatMessage>();
	chatMessage->Init(userID, message);

	// 채팅윈도우에 채팅전달
	UCChatWindow* pChatWindow = m_pGameInst->GetChatWindow();
	pChatWindow->AddChatMessage(chatMessage);
}

