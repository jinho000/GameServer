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

void ChatMessagePacketHandler::DBThreadCheckDB()
{
	ServerDebug::LogInfo("DB work");

	// 닉네임 검증
	// 세션이 가지고 있는 닉네임과 일치하는지 검사
	std::shared_ptr<SessionUserDBData> sessionUserDB = m_TCPSession->GetLink<SessionUserDBData>(EDBTable::USER);
	size_t deleteCharIndex = sessionUserDB->CheckNickName(m_packet->NickName);
	if (-1 == deleteCharIndex)
	{
		ServerDebug::LogInfo("Check Chat Nickname Fail");
		return;
	}
	ServerDebug::LogInfo("Check Chat Nickname OK");

	// 디비에 넣기
	// 세션의 유저정보를 가져와 ID, nickname, message를 달아 디비에 넣기
	FCharacterInfo characterInfo = sessionUserDB->GetCharacter(m_packet->NickName);
	ChattingTable_InsertChatting insertChatQuery(characterInfo.UserIndex, characterInfo.NickName, m_packet->Message);
	if (false == insertChatQuery.DoQuery())
	{
		ServerDebug::LogInfo("Insert Message Fail");
		return;
	}
	ServerDebug::LogInfo("insert DB OK");

	NetQueue::EnQueue(std::bind(&ChatMessagePacketHandler::NetThreadSendResult, std::dynamic_pointer_cast<ChatMessagePacketHandler>(shared_from_this())));
}

void ChatMessagePacketHandler::NetThreadSendResult()
{
	// 브로드캐스팅
	// 채팅메세지패킷은 UTF8로 받아 그대로 전달
	ServerSerializer sr;
	(*m_packet) >> sr;

	// 연결된 모든 세션에 패킷전달
	m_TCPSession->GetParent<TCPListener>()->BroadCast(sr.GetBuffer());
}

void ChatMessagePacketHandler::Start()
{
	ServerDebug::LogInfo("ChatMessage Packet");

	std::string nickName;
	std::string message;
	ServerString::UTF8ToANSI(m_packet->NickName, nickName);
	ServerString::UTF8ToANSI(m_packet->Message, message);

	ServerDebug::LogInfo("User NickName: " + nickName);
	ServerDebug::LogInfo("Message: " + message);

	// DBQueue 시작
	DBQueue::EnQueue(std::bind(&ChatMessagePacketHandler::DBThreadCheckDB, std::dynamic_pointer_cast<ChatMessagePacketHandler>(shared_from_this())));
}

