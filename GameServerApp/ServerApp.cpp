#include "pch.h"
#include "ServerApp.h"

#include <conio.h>

#include <GameServerNet/TCPListener.h>
#include <GameServerNet/TCPSession.h>
#include <GameServerNet/PacketConvertor.h>
#include <GameServerNet/PacketHandlerHeader.h>
#include <GameServerNet/PacketDispatcher.h>

PacketDispatcher<TCPSession> dispatcher;

void ServerApp::Start()
{
	ServerDebug::Initialize();

	TCPListener listener("localhost", 30000, [](PtrSTCPSession _tcpSession) {
		ServerDebug::LogInfo("접속자가 있습니다");
		_tcpSession->SetCallBack([](PtrSTCPSession _tcpSession, const std::vector<uint8_t>& _buffer) {

			// 패킷 처리
			PacketConvertor convertor(_buffer);
			// 패킷에 대한 처리 프로세스 가져오기
			const PacketHandler<TCPSession>& handler = dispatcher.GetHandler(convertor.GetPacketType());
			// 패킷 처리 실행
			handler(_tcpSession, convertor.GetPacket());

			},
			[](PtrSTCPSession _tcpSession) {
				ServerDebug::LogInfo("접속자 접속 종료");
			});
	});


	ServerDebug::Destroy();
}
