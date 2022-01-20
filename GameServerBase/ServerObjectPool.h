#pragma once

// 용도 :
// 분류 :
// 첨언 :
// using DataType = int;

template<typename DataType>
class ServerObjectPool
{
private: // member var
	std::deque<DataType*>	m_poolQueue;
	std::mutex				m_queueLock;

public: // default
	ServerObjectPool() = default;
	~ServerObjectPool() = default;

	ServerObjectPool(const ServerObjectPool& _other) = delete;
	ServerObjectPool(ServerObjectPool&& _other) = delete;

protected:
	ServerObjectPool& operator=(const ServerObjectPool& _other) = delete;
	ServerObjectPool& operator=(const ServerObjectPool&& _other) = delete;

private:

public: // member Func
	DataType* Pop()
	{
		std::lock_guard<std::mutex> lock(m_queueLock);
		if (m_poolQueue.empty())
		{
			return new DataType();
		}

		DataType* newData = m_poolQueue.front();
		m_poolQueue.pop_front();
		
		return newData;
	}

	void Push(DataType* _data)
	{
		std::lock_guard<std::mutex> lock(m_queueLock);
		m_poolQueue.push_back(_data);
	}
};

