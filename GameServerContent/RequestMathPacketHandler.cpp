#include "pch.h"
#include "RequestMathPacketHandler.h"
#include "ContentManager.h"

void RequestMathPacketHandler::Start()
{
	ContentManager::GetInst()->AddMatchQueue(m_packet->PlayerID);
}
