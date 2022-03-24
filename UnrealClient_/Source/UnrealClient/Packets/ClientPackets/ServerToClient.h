#pragma once
#include "ServerPacketBase.h"

class LoginResultPacket : public ServerPacketBase                    
{                                                               
public:                                                         
	EResultCode LoginResultCode;
                                                                
public:                                                         
    LoginResultPacket()                                               
        : ServerPacketBase(PacketType::LoginResult)                    
        , LoginResultCode()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~LoginResultPacket() {}             
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(LoginResultCode);
    }                                                           
                                                                
    void Serialize(ServerSerializer& _Serializer)           
    {                                                           
        ServerPacketBase::Serialize(_Serializer);              
        _Serializer.WriteEnum(LoginResultCode);

    }                                                           
                                                                
    void DeSerialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        _Serializer.ReadEnum(LoginResultCode);

    }                                                           
};                                                              

