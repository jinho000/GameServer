#pragma once
#include <GameServerBase/ServerBaseObject.h>
#include "IPEndPoint.h"
#include "GameServerBase/ServerQueue.h"

// 리슨소켓을 만들고 클라이언트 접속을 처리하는 클래스
// 세션을 미리 만들어두고 클라이언트의 접속을 기다린다
// 클라이언트의 접속이 오면 세션과 연결시킨다
// 클라와연결된 세션정보들을 가지고 브로드캐스팅을 처리한다
class ServerQueue;
class TCPSession;
class TCPListener : public ServerBaseObject
{
	friend class TCPSession;
	static UINT listenThreadCount;

private: // member var
	SOCKET												m_listenerSocket;
	IPEndPoint											m_ipEndPoint;
	const ServerQueue*									m_pNetQueue;
	std::function<void(std::shared_ptr<TCPSession>)>	m_acceptCallback; // 클라이언트접속 완료 후 호출될 함수
	std::function<void(BOOL, DWORD, LPOVERLAPPED)>		m_listenCallback; // 클라이언트가 접속했을떄 호출되는 함수
	
	std::vector<std::shared_ptr<TCPSession>>			m_sessionPool;	  // 전체 세션을 가진 풀
	std::deque<std::shared_ptr<TCPSession>>				m_acceptPool;
	std::mutex											m_acceptPoolLock;

	std::unordered_map<__int64, std::shared_ptr<TCPSession>>	m_connectionPool;
	std::mutex													m_connectionPoolLock;

public: // default
	TCPListener();
	~TCPListener();

	TCPListener(const TCPListener& _other) = delete;
	TCPListener(TCPListener&& _other) = delete;
	TCPListener& operator=(const TCPListener& _other) = delete;
	TCPListener& operator=(const TCPListener&& _other) = delete;

private:
	void CloseSocket(); // listen 소켓 종료

	// session을 만들고 accept함수 실행
	// 재활용할 세션이 있는경우 재활용할 세션 사용
	void CreateAcceptSession();

	// 클라이언트 접속 요청 이벤트 발생시 호출함수
	void OnAccept(BOOL _result, DWORD _byteSize, LPOVERLAPPED _overlapped);

	// 클라에 접속된 세션 종료하기
	void CloseSession(PtrSTCPSession _tcpSession);

public: // member Func
	void Initialize(const std::string _ip, int _port, const std::function<void(std::shared_ptr<TCPSession>)>& _acceptCallback);
	void StartAccept(UINT _backLog);

	void BindNetQueue(const ServerQueue& _workQueue);

	void BroadCast(const std::vector<uint8_t>& _buffer, PtrSTCPSession _exceptSession);
	void BroadCast(const std::vector<uint8_t>& _buffer);

};

