#pragma once
#include "ServerPacketBase.h"

class ChatMessagePacket : public ServerPacketBase                    
{                                                               
public:                                                         
	std::string ID;
	std::string Message;
                                                                
public:                                                         
    ChatMessagePacket()                                               
        : ServerPacketBase(PacketType::ChatMessage)                    
        , ID()
        , Message()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~ChatMessagePacket() {}             
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(ID) + DataSizeCheck(Message);
    }                                                           
                                                                
    void Serialize(ServerSerializer& _Serializer)           
    {                                                           
        ServerPacketBase::Serialize(_Serializer);              
        _Serializer << ID;
        _Serializer << Message;

    }                                                           
                                                                
    void DeSerialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        _Serializer >> ID;
        _Serializer >> Message;

    }                                                           
};                                                              

