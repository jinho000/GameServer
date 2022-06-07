#include <iostream>
#include <GameServerBase/pch.h>
#include <GameServerNet/pch.h>
#include <GameServerBase/ServerQueue.h>
#include <GameServerBase/ServerDebug.h>
#include <GameServerNet/TCPListener.h>
#include <GameServerNet/TCPSession.h>
#include <GameServerNet/UDPSession.h>
#include <GameServerNet/ServerHelper.h>
#include <GameServerNet/IPEndPoint.h>


void IOCallback(std::shared_ptr<UDPSession> _s, const std::vector<unsigned char>& _b, IPEndPoint& _rEP)
{
	int a = 0;
}

HANDLE IOCPHandle = NULL;
std::thread iocpThread;

void IOCPWorker()
{
	DWORD		 lpNumberOfBytesTransferred;
	ULONG_PTR	 lpCompletionKey;
	LPOVERLAPPED lpOverlapped;
	DWORD		 dwMilliseconds = INFINITE;

	GetQueuedCompletionStatus(IOCPHandle
		, &lpNumberOfBytesTransferred
		, &lpCompletionKey
		, &lpOverlapped
		, dwMilliseconds
	);

	int a = 0;
}

void InitIOCP()
{
	IOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, /*스레드 개수*/ 1);
	iocpThread = std::thread(IOCPWorker);


}

using namespace std;

// 리시브로 받은 데이터를 처리하기위한 버퍼
// TCP의 경우 데이터의 경계가 없기 때문에 패킷의 전체데이터를 확인 후 처리해야한다
std::vector<uint8_t>	m_recvReadBuffer;
int						m_packetSize;

void RecvCallback(const std::vector<uint8_t>& buffer)
{
	int a = 0;
}

void OnRecv(const char* _data, DWORD _byteSize)
{
	// 데이터를 받아 저장	
	for (size_t i = 0; i < _byteSize; i++)
	{
		m_recvReadBuffer.push_back(_data[i]);
	}

	// 패킷 크기가 저장된 경우
	// 2번째 데이터에 패킷의 크기가 저장된다
	if (2 <= m_recvReadBuffer.size())
	{
		m_packetSize = m_recvReadBuffer[1];
	}
	
	// 전체 데이터가 채워질 경우만 콜백함수 실행
	if (m_packetSize <= m_recvReadBuffer.size())
	{
		std::vector<uint8_t> buffer;
		buffer.assign(m_recvReadBuffer.begin(), m_recvReadBuffer.begin() + m_packetSize);
		RecvCallback(buffer);

		// 사용한 버퍼데이터는 제외하고 나머지 데이터를 세팅해줘야한다
		m_recvReadBuffer.erase(m_recvReadBuffer.begin(), m_recvReadBuffer.begin() + m_packetSize);

		// 패킷 크기 초기화
		if (m_recvReadBuffer.size() < 2)
		{
			m_packetSize = -1;
		}
	}
}

int main()
{
	// m_recvBuffer 초기화
	// 버퍼 초기 크기는 1024
	//m_recvReadBuffer.reserve(1024);
	//m_packetSize = -1;

	// 테스트1 
	// 데이터가 하나만 온 경우
	{
		//char data[1] = {3};
		//DWORD byteSize = 1;
		//OnRecv(data, byteSize);
	}

	// 테스트2 
	// 데이터가 2개 온 경우
	{		
		//const DWORD byteSize = 2;
		//char data[byteSize] = { 3, 5 };
		//OnRecv(data, byteSize);
	}

	// 테스트3
	// 패킷 크기보다 작게온경우
	{
		//const DWORD byteSize = 4;
		//char data[byteSize] = { 3, 10, 2, 5 };
		//OnRecv(data, byteSize);
	}

	// 테스트4
	// 패킷 크기와 동일하게 온 경우
	{
		//const DWORD byteSize = 4;
		//char data[byteSize] = { 3, 4, 1, 2 };
		//OnRecv(data, byteSize);
	}

	// 테스트5
	// 패킷 크기보다 크게 온경우
	{
		//const DWORD byteSize = 6;
		//char data[byteSize] = { 3, 4, 1, 2, 2, 3 };
		//OnRecv(data, byteSize);
		//OnRecv(data, byteSize);
	}

	std::string str("Test");

	cout << sizeof(str) << endl;

	return 0;
}
