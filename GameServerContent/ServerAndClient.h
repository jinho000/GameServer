#pragma once
#include "ServerPacketBase.h"

class ChatMessagePacket : public ServerPacketBase                    
{                                                               
public:                                                         
	std::string NickName;
	std::string Message;
                                                                
public:                                                         
    ChatMessagePacket()                                               
        : ServerPacketBase(PacketType::ChatMessage)                    
        , NickName()
        , Message()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~ChatMessagePacket() {}             
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(NickName) + DataSizeCheck(Message);
    }                                                           
                                                                
    void Serialize(ServerSerializer& _Serializer)           
    {                                                           
        ServerPacketBase::Serialize(_Serializer);              
        _Serializer << NickName;
        _Serializer << Message;

    }                                                           
                                                                
    void Deserialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        _Serializer >> NickName;
        _Serializer >> Message;

    }                                                           
};                                                              

class PlayerComeInPacket : public ServerPacketBase                    
{                                                               
public:                                                         
	FPlayerUpdateData PlayerData;
                                                                
public:                                                         
    PlayerComeInPacket()                                               
        : ServerPacketBase(PacketType::PlayerComeIn)                    
        , PlayerData()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~PlayerComeInPacket() {}             
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(PlayerData);
    }                                                           
                                                                
    void Serialize(ServerSerializer& _Serializer)           
    {                                                           
        ServerPacketBase::Serialize(_Serializer);              
        PlayerData.Serialize(_Serializer);

    }                                                           
                                                                
    void Deserialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        PlayerData.Deserialize(_Serializer);

    }                                                           
};                                                              

