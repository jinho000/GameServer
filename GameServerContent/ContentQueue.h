#pragma once

// 게임의 컨텐츠에 관련된 일을 처리
class ContentQueue
{
private: // Member Function
	static ServerQueue WorkQueue;

public: // default
	ContentQueue() = default;
	~ContentQueue() = default;

	ContentQueue(const ContentQueue& _other) = delete;
	ContentQueue(ContentQueue&& _other) = delete;
	ContentQueue& operator=(const ContentQueue& _other) = delete;
	ContentQueue& operator=(const ContentQueue&& _other) = delete;

public: // member Func
	static void Init();
	static void Destroy();
	static void EnQueue(const std::function<void()>& _work);
};
