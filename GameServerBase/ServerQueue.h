#pragma once
#include "ServerNameBase.h"
#include "ServerIOCPWorker.h"
#include "ServerIOCP.h"

// 내가 일시키는 용 job
//struct PostJob : public std::enable_shared_from_this<PostJob>
//{
//	std::function<void()> task_;
//};

// 뭘 보내라는거죠? 일자체를 보내라는 의미가 됩니다.

// 비동기 파일입출력용 job
//struct OverlappedJob : public std::enable_shared_from_this<PostJob>
//{
//	// BOOL 성공 실패
//	// DWORD 받은 패킷이나 처리한 데이터의 길이
//	// LPOVERLAPPED 비동기 입출력의 정보를 담고 있는 OVERLAPPED의 포인터
//	std::function<void(BOOL _Result, DWORD _NumberOfBytes, LPOVERLAPPED)> task_;
//
//
//public:
//	OverlappedJob() {
//
//	}
//
//	~OverlappedJob()
//	{
//		int a = 0;
//	}
//};

// IOCP를 통해 일을 시키기 위한 클래스
// 내부에 스레드 풀이 있으며 Enqueue를 통해 작업을 전달하기만 하면 된다(생산자 소비자 패턴)
class ServerQueue : public ServerNameBase
{
private:
	// 내가 일시키는 용 job
	struct PostWork : public std::enable_shared_from_this<PostWork>
	{
		std::function<void()> work;
	};

private:
	// thread pool에서 사용할 함수
	void WorkThread(std::shared_ptr<ServerIOCPWorker> _worker, const std::string& _threadName);

	// thread local용 
	template<typename LocalDataType>
	void WorkThreadLocal(std::shared_ptr<ServerIOCPWorker> _worker, const std::string& _Name, std::function<void(LocalDataType*)> _initLocal)
	{
		if (nullptr == this)
		{
			ServerDebug::AssertDebugMsg("큐 쓰레드 생성에 실패했습니다.");
		}

		// 스레드 이름 설정
		ServerThread::SetThreadName(_Name + " " + std::to_string(_worker->GetIndex()));

		// thread local 영역에 필요한 데이터 생성
		LocalDataType* threadLocalData = ServerThread::CreateThreadLocalData<LocalDataType>();

		// init local data
		if (nullptr != _initLocal)
		{
			_initLocal(threadLocalData);
		}

		this->RunThread(_worker);

		// thread local 데이터 삭제
		ServerThread::DeleteThreadLocalData<LocalDataType>();
	}

public: // type
	//enum class WORK_TYPE : char
	//{
	//	Default,	// 포스트큐 사용 타입
	//	Extension	// GetQueuedCompletionStatusEx로 여러개 사용 타입
	//};

	enum class WORK_MSG
	{
		PostWork = -2,
		WORK_DESTROY = -1,	
	};

private: // member var
	ServerIOCP m_Iocp;

public: // default
	ServerQueue();
	~ServerQueue();

	ServerQueue(const ServerQueue& _other) = delete;
	ServerQueue(ServerQueue&& _other) = delete;
	ServerQueue& operator=(const ServerQueue& _other) = delete;
	ServerQueue& operator=(const ServerQueue&& _other) = delete;

private:
	void RunThread(std::shared_ptr<ServerIOCPWorker> _worker);

public: // member Func

	// queue 초기화
	void Initialize(int threadCount, const std::string& _ThreadName = "WorkThread");

	// thread local 사용
	template<typename LocalDataType>
	void InitializeLocalData(int threadCount, const std::string& _ThreadName, std::function<void(LocalDataType*)> _initLocal = nullptr)
	{
		m_Iocp.InitializeLocalData<LocalDataType>(std::bind(&ServerQueue::WorkThreadLocal<LocalDataType>, this, std::placeholders::_1, _ThreadName, _initLocal), INFINITE, threadCount);
	}

	// 스레드 종료
	void Destroy();

	// queue에 작업 추가
	void Enqueue(const std::function<void()>& _work);


	// _socket: 등록할 소켓
	// _onIOCallback: 소켓에 IO이벤트가 일어날경우 호출될 함수
	bool RegistSocket(SOCKET _socket, const std::function<void(BOOL, DWORD, LPOVERLAPPED)>* _onIOCallback) const;

};

