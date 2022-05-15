#include "pch.h"
#include "DeleteCharacterPacketHandler.h"
#include <GameServerBase/ServerString.h>
#include <GameServerNet/TCPSession.h>
#include <GameServerCore/DBQueue.h>
#include <GameServerCore/NetQueue.h>

#include "UserTable.h"
#include "CharacterTable.h"
#include "SessionUserDBData.h"
#include "DBTableEHeader.h"
#include "ContentStruct.h"

void DeleteCharacterPacketHandler::DBThreadWork()
{
	ServerDebug::LogInfo("Check DB");
	m_resultPacket.ResultCode = EResultCode::FAIL;
	m_resultPacket.DeleteCharNickName = m_packet->NickName;

	// 해당 닉네임이 있는지 확인
	CharacterTable_SelectNickName SelectQuery = CharacterTable_SelectNickName(m_packet->NickName);
	if (false == SelectQuery.DoQuery())
	{
		ServerDebug::LogInfo("Select Query Fail");
		NetQueue::EnQueue(std::bind(&DeleteCharacterPacketHandler::NetThreadSendResult, std::dynamic_pointer_cast<DeleteCharacterPacketHandler>(shared_from_this())));
		return;
	}

	// 세션이 가지고 있는 닉s네임과 일치하는지 검사
	std::shared_ptr<SessionUserDBData> sessionUserDB = m_TCPSession->GetLink<SessionUserDBData>(EDBTable::USER);
	size_t deleteCharIndex = sessionUserDB->CheckNickName(m_packet->NickName);
	if (-1 == deleteCharIndex)
	{
		ServerDebug::LogInfo("nickname Fail");
		NetQueue::EnQueue(std::bind(&DeleteCharacterPacketHandler::NetThreadSendResult, std::dynamic_pointer_cast<DeleteCharacterPacketHandler>(shared_from_this())));
		return;
	}

	// 디비에 캐릭터 삭제 처리 요청
	CharacterTable_DeleteCharacter deleteQuery = CharacterTable_DeleteCharacter((int)deleteCharIndex);
	if (false == deleteQuery.DoQuery())
	{
		ServerDebug::LogInfo("Fail InsertQuery");
		NetQueue::EnQueue(std::bind(&DeleteCharacterPacketHandler::NetThreadSendResult, std::dynamic_pointer_cast<DeleteCharacterPacketHandler>(shared_from_this())));
		return;
	}
	ServerDebug::LogInfo("Delete OK");
	m_resultPacket.ResultCode = EResultCode::OK;
	
	// 캐릭터 삭제 완료 후 세션의 정보와 동기화
	sessionUserDB->DeleteCharacter(m_packet->NickName);
	NetQueue::EnQueue(std::bind(&DeleteCharacterPacketHandler::NetThreadSendResult, std::dynamic_pointer_cast<DeleteCharacterPacketHandler>(shared_from_this())));
}

void DeleteCharacterPacketHandler::NetThreadSendResult()
{
	ServerSerializer sr;
	m_resultPacket >> sr;
	m_TCPSession->Send(sr.GetBuffer());

	ServerDebug::LogInfo("Send Delete Charater Result");
}


void DeleteCharacterPacketHandler::Start()
{
	ServerDebug::LogInfo("Delete Character Packet");

	std::string nickName; ServerString::UTF8ToANSI(m_packet->NickName, nickName);
	ServerDebug::LogInfo(std::string("Delete NickName: ") + nickName);

	// DB에 처리 요청
	m_resultPacket.ResultCode = EResultCode::FAIL;
	DBQueue::EnQueue(std::bind(&DeleteCharacterPacketHandler::DBThreadWork, std::dynamic_pointer_cast<DeleteCharacterPacketHandler>(shared_from_this())));
}
