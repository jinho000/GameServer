#include <iostream>
#include <crtdbg.h>

#include <conio.h>

#include <GameServerPacket/pch.h>

#include <GameServerBase/ServerDebug.h>
#include <GameServerNet/TCPListener.h>
#include <GameServerNet/TCPSession.h>
#include <GameServerNet/TypeDefine.h>
#include <GameServerNet/ServerHelper.h>

#include <GameServerPacket/PacketConvertor.h>
#include <GameServerPacket/PacketDispatcher.h>
#include <GameServerPacket/DBQueue.h>


PacketDispatcher<TCPSession> dispatcher;

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 소켓 라이브러리 초기화
	ServerHelper::InitSocketLib();

	ServerDebug::Initialize();
	//DBQueue::Init();

	TCPListener listener(std::string("localhost"), 30001, [](PtrSTCPSession _tcpSession) {
		ServerDebug::LogInfo("접속자가 있습니다");
		_tcpSession->SetCallBack([](PtrSTCPSession _tcpSession, const std::vector<uint8_t>& _buffer) {
			// 패킷 처리
			// 패킷에 대한 처리 프로세스 가져오기
			// 패킷 처리 실행
			PacketConvertor convertor(_buffer);
			const PacketHandler<TCPSession>& handler = dispatcher.GetHandler(convertor.GetPacketType());
			handler(_tcpSession, convertor.GetPacket());
			},
			[](PtrSTCPSession _tcpSession) {
				ServerDebug::LogInfo("접속자 접속 종료");
			});
		});

	_getch();

	ServerDebug::Destroy();

    return 0;
}

