#pragma once
#include "ServerPacketBase.h"

class LoginPacket : public ServerPacketBase                    
{                                                               
public:                                                         
	std::string ID;
	std::string PW;
                                                                
public:                                                         
    LoginPacket()                                               
        : ServerPacketBase(PacketType::Login)                    
        , ID()
        , PW()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~LoginPacket() {}             
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(ID) + DataSizeCheck(PW);
    }                                                           
                                                                
    void Serialize(ServerSerializer& _Serializer)           
    {                                                           
        ServerPacketBase::Serialize(_Serializer);              
        _Serializer << ID;
        _Serializer << PW;

    }                                                           
                                                                
    void Deserialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        _Serializer >> ID;
        _Serializer >> PW;

    }                                                           
};                                                              

class JoinPacket : public ServerPacketBase                    
{                                                               
public:                                                         
	std::string ID;
	std::string PW;
                                                                
public:                                                         
    JoinPacket()                                               
        : ServerPacketBase(PacketType::Join)                    
        , ID()
        , PW()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~JoinPacket() {}             
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(ID) + DataSizeCheck(PW);
    }                                                           
                                                                
    void Serialize(ServerSerializer& _Serializer)           
    {                                                           
        ServerPacketBase::Serialize(_Serializer);              
        _Serializer << ID;
        _Serializer << PW;

    }                                                           
                                                                
    void Deserialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        _Serializer >> ID;
        _Serializer >> PW;

    }                                                           
};                                                              

class CreateCharacterPacket : public ServerPacketBase                    
{                                                               
public:                                                         
	std::string NickName;
                                                                
public:                                                         
    CreateCharacterPacket()                                               
        : ServerPacketBase(PacketType::CreateCharacter)                    
        , NickName()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~CreateCharacterPacket() {}             
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(NickName);
    }                                                           
                                                                
    void Serialize(ServerSerializer& _Serializer)           
    {                                                           
        ServerPacketBase::Serialize(_Serializer);              
        _Serializer << NickName;

    }                                                           
                                                                
    void Deserialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        _Serializer >> NickName;

    }                                                           
};                                                              

