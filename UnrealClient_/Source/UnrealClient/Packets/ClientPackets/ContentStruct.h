#pragma once
#include <string>
#include "ServerSerializer.h"

// 컨텐츠의 구조체는 앞에 F를 붙인다

struct FCharacterInfo
{
public:
	int			Index;
	std::string NickName;
	int			UserIndex;
	float		Att;
	float		Hp;
	int			LastRoomID;
	float		RoomX;
	float		RoomY;
	float		RoomZ;

	FCharacterInfo()
		: Index(-1)
	{}

	int GetDataSize()
	{
		// int, float 개수: 8, 문자열개수저장변수:4, 문자열개수
		return (4 * 8) + 4 + static_cast<int>(NickName.size());
	}

	void Serialize(ServerSerializer& _Ser)
	{
		_Ser << Index;
		_Ser << NickName;
		_Ser << UserIndex;
		_Ser << Att;
		_Ser << Hp;
		_Ser << LastRoomID;
		_Ser << RoomX;
		_Ser << RoomY;
		_Ser << RoomZ;
	}

	void Deserialize(ServerSerializer& _Ser)
	{
		_Ser >> Index;
		_Ser >> NickName;
		_Ser >> UserIndex;
		_Ser >> Att;
		_Ser >> Hp;
		_Ser >> LastRoomID;
		_Ser >> RoomX;
		_Ser >> RoomY;
		_Ser >> RoomZ;
	}
};

struct FPlayerUpdateData
{
	uint64_t PlayerID;
	uint64_t SessionIdx;
	uint64_t PlayerIdx;
	FVector4 Dir;
	FVector4 Pos;
	FVector4 Rot;
	int State;

	FPlayerUpdateData(uint64_t playerID)
		: PlayerID(playerID)
		, SessionIdx(-1)
		, PlayerIdx(-1)
		, State(-1)
	{}

	FPlayerUpdateData()
		: PlayerID()
		, SessionIdx(-1)
		, PlayerIdx(-1)
		, State(-1)
	{}

	template<typename EnumType>
	EnumType GetState()
	{
		return static_cast<EnumType>(State);
	}

	template<typename EnumType>
	void SetState(EnumType _Type)
	{
		State = static_cast<int>(_Type);
	}


	int GetDataSize()
	{
		return sizeof(FPlayerUpdateData);
	}

	void Serialize(ServerSerializer& _Ser)
	{
		_Ser << PlayerID;
		_Ser << SessionIdx;
		_Ser << PlayerIdx;
		_Ser << Dir;
		_Ser << Pos;
		_Ser << Rot;
		_Ser << State;
	}

	void Deserialize(ServerSerializer& _Ser)
	{
		_Ser >> PlayerID;
		_Ser >> SessionIdx;
		_Ser >> PlayerIdx;
		_Ser >> Dir;
		_Ser >> Pos;
		_Ser >> Rot;
		_Ser >> State;
	}


	~FPlayerUpdateData() {
	}
};