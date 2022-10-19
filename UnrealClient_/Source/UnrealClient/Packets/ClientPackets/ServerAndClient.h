#pragma once
#include "ServerPacketBase.h"

class ChatMessagePacket : public ServerPacketBase                    
{                                                               
public:                                                         
	std::string NickName;
	std::string Message;
	int sessionID;
                                                                
public:                                                         
    ChatMessagePacket()                                               
        : ServerPacketBase(PacketType::ChatMessage)                    
        , NickName()
        , Message()
        , sessionID()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~ChatMessagePacket() {}             
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(NickName) + DataSizeCheck(Message) + DataSizeCheck(sessionID);
    }                                                           
                                                                
    void Serialize(ServerSerializer& _Serializer)           
    {                                                           
        ServerPacketBase::Serialize(_Serializer);              
        _Serializer << NickName;
        _Serializer << Message;
        _Serializer << sessionID;

    }                                                           
                                                                
    void Deserialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        _Serializer >> NickName;
        _Serializer >> Message;
        _Serializer >> sessionID;

    }                                                           
};                                                              

