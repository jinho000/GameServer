#include "pch.h"
#include "ServerTime.h"

ServerTime::ServerTime()
{
}

ServerTime::~ServerTime()
{
}

void ServerTime::Reset()
{
	Current_ = Timer_.now();
	Prev_ = Timer_.now();
}

float ServerTime::Update()
{
	Current_ = Timer_.now();
	DoubleDeltaTime = std::chrono::duration<double>(Current_ - Prev_).count();
	Prev_ = Current_;

	DeltaTime = static_cast<float>(DoubleDeltaTime);
	return DeltaTime;
}