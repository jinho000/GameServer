#pragma once
#include <random>

#include "ServerMathStruct.h"

class ServerMath
{
public:
};

class ServerRandom
{
	std::random_device rd;
	std::mt19937 gen;
	// std::uniform_int_distribution<int> dis;

public:
	int RandomInt(int _Min, int _Max)
	{
		std::uniform_int_distribution<int> dis(_Min, _Max);
		return dis(gen);
	}

	float Randomfloat(float _Min, float _Max)
	{
		std::uniform_real_distribution<float> dis(_Min, _Max);
		return dis(gen);
	}

public:
	ServerRandom()
		: gen(rd())
	{

	}

	ServerRandom(unsigned int _Seed)
		: gen(_Seed)
	{

	}
};
