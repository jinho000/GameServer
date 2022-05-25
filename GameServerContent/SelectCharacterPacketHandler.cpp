#include "pch.h"
#include "SelectCharacterPacketHandler.h"
#include <GameServerNet/TCPSession.h>
#include <GameServerCore/DBQueue.h>
#include "CharacterTable.h"
#include "SessionUserDBData.h"
#include "DBTableEHeader.h"

void SelectCharacterPacketHandler::NetThreadSendSelectResult()
{
	// 유저데이터 오브젝트 가져오기
	std::shared_ptr<SessionUserDBData> UserDBData = m_TCPSession->GetLink<SessionUserDBData>(EDBTable::USER);

	if (m_resultPacket.ResultCode == EResultCode::OK)
	{
		for (size_t i = 0; i < UserDBData->UserCharacterList.size(); i++)
		{
			if (UserDBData->UserCharacterList[i].NickName == m_packet->SelectCharNickName)
			{
				// 완료 결과 전송
				ServerDebug::LogInfo("Check OK");
				ServerDebug::LogInfo("Send Select Result");

				ServerSerializer sr;
				m_resultPacket.SelectCharNickName = m_packet->SelectCharNickName;
				m_resultPacket.GameSessionType = EGameSession::SESSION0;
				m_resultPacket >> sr;
				m_TCPSession->Send(sr.GetBuffer());


				// 선택한 캐릭터 정보 저장
				m_selectCharacter = UserDBData->UserCharacterList[i];

				// 세션에 유저 추가하기
				//InsertUserToSection();
				return;
			}
		}
	}

	ServerDebug::LogInfo("Check Fail");
	ServerDebug::LogInfo("Send Select Result");
	m_resultPacket.ResultCode = EResultCode::FAIL;
	ServerSerializer sr;
	m_resultPacket >> sr;
	m_TCPSession->Send(sr.GetBuffer());
}

void SelectCharacterPacketHandler::InsertUserToSection()
{
	// 세션에 유저 등록
	//GameSessionManager::GetInst()->InsertUser(EGameSession::SESSION0, m_TCPSession);
}

void SelectCharacterPacketHandler::DBThreadCheckSelectCharacter()
{
	ServerDebug::LogInfo("Check NickName");

	CharacterTable_SelectNickName SelectQuery = CharacterTable_SelectNickName(m_packet->SelectCharNickName);
	if (false == SelectQuery.DoQuery())
	{
		ServerDebug::LogInfo("Check DB NickName FAIl");
		m_resultPacket.ResultCode = EResultCode::FAIL;
		DBQueue::EnQueue(std::bind(&SelectCharacterPacketHandler::NetThreadSendSelectResult, std::dynamic_pointer_cast<SelectCharacterPacketHandler>(shared_from_this())));
		return;
	}

	ServerDebug::LogInfo("Check DB NickName OK");
	m_resultPacket.ResultCode = EResultCode::OK;
	DBQueue::EnQueue(std::bind(&SelectCharacterPacketHandler::NetThreadSendSelectResult, std::dynamic_pointer_cast<SelectCharacterPacketHandler>(shared_from_this())));
}

void SelectCharacterPacketHandler::Start()
{
	ServerDebug::LogInfo("SelectCharacter Packet");

	DBQueue::EnQueue(std::bind(&SelectCharacterPacketHandler::DBThreadCheckSelectCharacter, std::dynamic_pointer_cast<SelectCharacterPacketHandler>(shared_from_this())));
}
