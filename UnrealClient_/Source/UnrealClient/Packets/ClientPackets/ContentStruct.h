#pragma once
#include "ServerSerializer.h"
#include <string>

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

	int GetDataSize()
	{
		// int, float ����: 8, ���ڿ��������庯��:4, ���ڿ�����
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
