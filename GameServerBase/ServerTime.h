#pragma once

// 용도 :
// 분류 :
// 첨언 :
class ServerTime
{
public:
	// constrcuter destructer
	ServerTime();
	~ServerTime();

	// delete Function
	ServerTime(const ServerTime& _Other) = delete;
	ServerTime(ServerTime&& _Other) noexcept = delete;
	ServerTime& operator=(const ServerTime& _Other) = delete;
	ServerTime& operator=(ServerTime&& _Other) noexcept = delete;

	std::chrono::high_resolution_clock Timer_;
	std::chrono::steady_clock::time_point Current_;
	std::chrono::steady_clock::time_point Prev_;

	double DoubleDeltaTime;
	float DeltaTime;

	void Reset();

	float Update();

	float GetDeltaTime()
	{
		return DeltaTime;
	}

protected:


private:

};

