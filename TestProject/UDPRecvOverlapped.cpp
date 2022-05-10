#include "pch.h"
#include "UDPRecvOverlapped.h"

UDPRecvOverlapped::UDPRecvOverlapped(std::weak_ptr<class UDPSession> _UDPSession)
	: UDPSession_(_UDPSession)
{

	memset(Buffer, 0x00, sizeof(Buffer));
	wsaBuffer.buf = Buffer;
	wsaBuffer.len = static_cast<ULONG>(sizeof(Buffer));
	numberofBytes_ = 0;
}

void UDPRecvOverlapped::Execute(BOOL Result, DWORD _ByteSize)
{
	std::shared_ptr<UDPSession> udpSession = UDPSession_.lock();

	//IPEndPoint remoteEndPoint(udpSession->remoteAddr_.sin_addr.s_addr, htons(udpSession->remoteAddr_.sin_port));
	//if (nullptr == udpSession)
	//{
	//	GameServerDebug::AssertDebugMsg("if (nullptr == udpSession)");
	//	return;
	//}

	//if (0 == _ByteSize)
	//{
	//	udpSession->Recv();
	//	return;
	//}

	//udpSession->OnRecv(Buffer, _ByteSize);

}
