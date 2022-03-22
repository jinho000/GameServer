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
		ServerDebug::LogInfo("�����ڰ� �ֽ��ϴ�");
		_tcpSession->SetCallBack([](PtrSTCPSession _tcpSession, const std::vector<uint8_t>& _buffer) {

			// ��Ŷ ó��
			PacketConvertor convertor(_buffer);
			// ��Ŷ�� ���� ó�� ���μ��� ��������
			const PacketHandler<TCPSession>& handler = dispatcher.GetHandler(convertor.GetPacketType());
			// ��Ŷ ó�� ����
			handler(_tcpSession, convertor.GetPacket());

			},
			[](PtrSTCPSession _tcpSession) {
				ServerDebug::LogInfo("������ ���� ����");
			});
	});


	ServerDebug::Destroy();
}
