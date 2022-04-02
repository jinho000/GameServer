#include "pch.h"
#include "CreateCharacterPacketHandler.h"
#include <GameServerBase/ServerString.h>
#include <GameServerNet/TCPSession.h>
#include <GameServerCore/DBQueue.h>
#include <GameServerCore/NetQueue.h>
#include "ContentUserData.h"
#include "ContentHeader.h"
#include "CharacterTable.h"

CreateCharacterPacketHandler::CreateCharacterPacketHandler(PtrSTCPSession _TCPSession, std::shared_ptr<CreateCharacterPacket> _packet)
	: PacketHandlerBase(_TCPSession, _packet)
{
}

CreateCharacterPacketHandler::~CreateCharacterPacketHandler()
{
}

void CreateCharacterPacketHandler::DBThreadWork()
{
	ServerDebug::LogInfo("Check DB");

	// 해당 닉네임이 있는지 확인
	CharacterTable_SelectNickName SelectQuery = CharacterTable_SelectNickName(m_packet->NickName);
	if (true == SelectQuery.DoQuery())
	{
		m_resultPacket.ResultCode = EResultCode::FAIL;
		ServerDebug::LogInfo("NickName is already exist");
		NetQueue::EnQueue(std::bind(&CreateCharacterPacketHandler::NetThreadSendResult, std::dynamic_pointer_cast<CreateCharacterPacketHandler>(shared_from_this())));
		return;
	}

	// 디비에 캐릭터 생성 처리 요청
	std::shared_ptr<ContentUserData> Ptr = m_TCPSession->GetLink<ContentUserData>(EDataIndex::USERDATA);
	CharacterTable_CreateCharacter InsertQuery = CharacterTable_CreateCharacter(m_packet->NickName, Ptr->userData->Index);
	if (false == InsertQuery.DoQuery())
	{
		ServerDebug::AssertDebugMsg("Fail InsertQuery");
		return;
	}

	// 생성한 캐릭터 정보 가져오기
	CharacterTable_SelectNickName CharInfoSelectQuery(m_packet->NickName);
	if (false == CharInfoSelectQuery.DoQuery())
	{
		ServerDebug::AssertDebugMsg("Fail Select Query");
		return;
	}

	m_resultPacket.ResultCode = EResultCode::OK;
	m_resultPacket.CharacterInfo.Index = CharInfoSelectQuery.RowData->Index;
	m_resultPacket.CharacterInfo.NickName = CharInfoSelectQuery.RowData->NickName;
	m_resultPacket.CharacterInfo.UserIndex = CharInfoSelectQuery.RowData->UserIndex;
	m_resultPacket.CharacterInfo.Att = CharInfoSelectQuery.RowData->Att;
	m_resultPacket.CharacterInfo.Hp = CharInfoSelectQuery.RowData->Hp;
	m_resultPacket.CharacterInfo.LastRoomID = CharInfoSelectQuery.RowData->LastRoomID;
	m_resultPacket.CharacterInfo.RoomX = CharInfoSelectQuery.RowData->RoomX;
	m_resultPacket.CharacterInfo.RoomY = CharInfoSelectQuery.RowData->RoomY;
	m_resultPacket.CharacterInfo.RoomZ = CharInfoSelectQuery.RowData->RoomZ;

	ServerDebug::LogInfo("Check DB OK");

	NetQueue::EnQueue(std::bind(&CreateCharacterPacketHandler::NetThreadSendResult, std::dynamic_pointer_cast<CreateCharacterPacketHandler>(shared_from_this())));
}

void CreateCharacterPacketHandler::NetThreadSendResult()
{
	ServerSerializer sr;
	m_resultPacket >> sr;
	m_TCPSession->Send(sr.GetBuffer());

	ServerDebug::LogInfo("Send Create Charater Result");
}

void CreateCharacterPacketHandler::Start()
{
	ServerDebug::LogInfo("Create Character Packet");

	std::string nickName; ServerString::UTF8ToANSI(m_packet->NickName, nickName);
	ServerDebug::LogInfo(std::string("Character NickName: ") + nickName);
	
	// DB에 처리 요청
	m_resultPacket.ResultCode = EResultCode::FAIL;
	DBQueue::EnQueue(std::bind(&CreateCharacterPacketHandler::DBThreadWork, std::dynamic_pointer_cast<CreateCharacterPacketHandler>(shared_from_this())));
}
