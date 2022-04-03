#include "ChatMessagePacketHandler.h"
#include <Kismet/GameplayStatics.h>
#include "../../Play/Chat/CChatMessage.h"
#include "../../Global/CGameInstance.h"
#include "../../Play/Chat/CChatWindow.h"

void ChatMessagePacketHandler::Start()
{
	// ��Ŷ �м�
	FString userID = FUTF8ToTCHAR(m_packet->ID.c_str()).Get();
	FString message = FUTF8ToTCHAR(m_packet->Message.c_str()).Get();

	// ä�� ������Ʈ 
	UCChatMessage* chatMessage = NewObject<UCChatMessage>();
	chatMessage->Init(userID, message);

	// ä�������쿡 ä������
	UCChatWindow* pChatWindow = m_pGameInst->GetChatWindow();
	pChatWindow->AddChatMessage(chatMessage);
}

