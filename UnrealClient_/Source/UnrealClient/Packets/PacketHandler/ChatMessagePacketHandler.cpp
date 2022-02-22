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
	// ��Ŷ �м�
	FString userID = FUTF8ToTCHAR(m_packet->m_userID.c_str()).Get();
	FString message = FUTF8ToTCHAR(m_packet->m_chatMessage.c_str()).Get();

	// ä�� ������Ʈ 
	UCChatMessage* chatMessage = NewObject<UCChatMessage>();
	chatMessage->Init(userID, message);

	// ä�������쿡 ä������
	UCChatWindow* pChatWindow = m_pGameInst->GetChatWindow();
	pChatWindow->AddChatMessage(chatMessage);
}

