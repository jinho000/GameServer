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

class CharacterListPacket : public ServerPacketBase                    
{                                                               
public:                                                         
	std::vector<FCharacterInfo> CharacterList;
                                                                
public:                                                         
    CharacterListPacket()                                               
        : ServerPacketBase(PacketType::CharacterList)                    
        , CharacterList()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~CharacterListPacket() {}             
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(CharacterList);
    }                                                           
                                                                
    void Serialize(ServerSerializer& _Serializer)           
    {                                                           
        ServerPacketBase::Serialize(_Serializer);              
        _Serializer.WriteVector(CharacterList);

    }                                                           
                                                                
    void Deserialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        _Serializer.ReadVector(CharacterList);

    }                                                           
};                                                              

class CreateCharacterResultPacket : public ServerPacketBase                    
{                                                               
public:                                                         
	FCharacterInfo CharacterInfo;
	EResultCode ResultCode;
                                                                
public:                                                         
    CreateCharacterResultPacket()                                               
        : ServerPacketBase(PacketType::CreateCharacterResult)                    
        , CharacterInfo()
        , ResultCode()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~CreateCharacterResultPacket() {}             
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(CharacterInfo) + DataSizeCheck(ResultCode);
    }                                                           
                                                                
    void Serialize(ServerSerializer& _Serializer)           
    {                                                           
        ServerPacketBase::Serialize(_Serializer);              
        CharacterInfo.Serialize(_Serializer);
        _Serializer.WriteEnum(ResultCode);

    }                                                           
                                                                
    void Deserialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        CharacterInfo.Deserialize(_Serializer);
        _Serializer.ReadEnum(ResultCode);

    }                                                           
};                                                              

class SelectCharacterResultPacket : public ServerPacketBase                    
{                                                               
public:                                                         
	EResultCode ResultCode;
	std::string SelectCharNickName;
                                                                
public:                                                         
    SelectCharacterResultPacket()                                               
        : ServerPacketBase(PacketType::SelectCharacterResult)                    
        , ResultCode()
        , SelectCharNickName()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~SelectCharacterResultPacket() {}             
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(ResultCode) + DataSizeCheck(SelectCharNickName);
    }                                                           
                                                                
    void Serialize(ServerSerializer& _Serializer)           
    {                                                           
        ServerPacketBase::Serialize(_Serializer);              
        _Serializer.WriteEnum(ResultCode);
        _Serializer << SelectCharNickName;

    }                                                           
                                                                
    void Deserialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        _Serializer.ReadEnum(ResultCode);
        _Serializer >> SelectCharNickName;

    }                                                           
};                                                              

class InsertSectionResultPacket : public ServerPacketBase                    
{                                                               
public:                                                         
	EResultCode ResultCode;
                                                                
public:                                                         
    InsertSectionResultPacket()                                               
        : ServerPacketBase(PacketType::InsertSectionResult)                    
        , ResultCode()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~InsertSectionResultPacket() {}             
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(ResultCode);
    }                                                           
                                                                
    void Serialize(ServerSerializer& _Serializer)           
    {                                                           
        ServerPacketBase::Serialize(_Serializer);              
        _Serializer.WriteEnum(ResultCode);

    }                                                           
                                                                
    void Deserialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        _Serializer.ReadEnum(ResultCode);

    }                                                           
};                                                              

