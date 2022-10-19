#include "pch.h"
#include "ChatMessagePacketHandler.h"
#include "GameServerBase/ServerDebug.h"
#include "GameServerBase/ServerString.h"
#include "GameServerNet/TCPSession.h"
#include "GameServerNet/TCPListener.h"
#include <GameServerCore/DBQueue.h>
#include <GameServerCore/NetQueue.h>
#include "SessionUserDBData.h"
#include "DBTableEHeader.h"
#include "ChattingTable.h"
#include "ContentManager.h"


void ChatMessagePacketHandler::Start()
{
	ServerDebug::LogInfo("ChatMessage Packet");

	int sessionID = m_packet->sessionID;
	std::string nickName;
	std::string message;
	ServerString::UTF8ToANSI(m_packet->NickName, nickName);
	ServerString::UTF8ToANSI(m_packet->Message, message);

	ServerDebug::LogInfo("User NickName: " + nickName);
	ServerDebug::LogInfo("Message: " + message);
	ServerDebug::LogInfo("SessionID: " + std::to_string(sessionID));

	ContentManager::GetInst()->BroadCastTCPInSession(m_packet->sessionID, m_packet);

}

