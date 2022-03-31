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
                                                                
    void Deserialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        _Serializer.ReadEnum(LoginResultCode);

    }                                                           
};                                                              

class JoginResultPacket : public ServerPacketBase                    
{                                                               
public:                                                         
	EResultCode JoginResultCode;
                                                                
public:                                                         
    JoginResultPacket()                                               
        : ServerPacketBase(PacketType::JoginResult)                    
        , JoginResultCode()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~JoginResultPacket() {}             
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(JoginResultCode);
    }                                                           
                                                                
    void Serialize(ServerSerializer& _Serializer)           
    {                                                           
        ServerPacketBase::Serialize(_Serializer);              
        _Serializer.WriteEnum(JoginResultCode);

    }                                                           
                                                                
    void Deserialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        _Serializer.ReadEnum(JoginResultCode);

    }                                                           
};                                                              
