#pragma once
#include "ServerPacketBase.h"

class LoginResultPacket : public ServerPacketBase                    
{                                                               
public:                                                         
	ELoginResultCode LoginResultCode;
	int UDPPort;
                                                                
public:                                                         
    LoginResultPacket()                                               
        : ServerPacketBase(PacketType::LoginResult)                    
        , LoginResultCode()
        , UDPPort()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~LoginResultPacket() {}             
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(LoginResultCode) + DataSizeCheck(UDPPort);
    }                                                           
                                                                
    void Serialize(ServerSerializer& _Serializer)           
    {                                                           
        ServerPacketBase::Serialize(_Serializer);              
        _Serializer.WriteEnum(LoginResultCode);
        _Serializer << UDPPort;

    }                                                           
                                                                
    void Deserialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        _Serializer.ReadEnum(LoginResultCode);
        _Serializer >> UDPPort;

    }                                                           
};                                                              

class JoginResultPacket : public ServerPacketBase                    
{                                                               
public:                                                         
	EJoinResultCode JoginResultCode;
                                                                
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
	ECreateCharacterResultCode ResultCode;
                                                                
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

class DeleteCharacterResultPacket : public ServerPacketBase                    
{                                                               
public:                                                         
	EResultCode ResultCode;
	std::string DeleteCharNickName;
                                                                
public:                                                         
    DeleteCharacterResultPacket()                                               
        : ServerPacketBase(PacketType::DeleteCharacterResult)                    
        , ResultCode()
        , DeleteCharNickName()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~DeleteCharacterResultPacket() {}             
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(ResultCode) + DataSizeCheck(DeleteCharNickName);
    }                                                           
                                                                
    void Serialize(ServerSerializer& _Serializer)           
    {                                                           
        ServerPacketBase::Serialize(_Serializer);              
        _Serializer.WriteEnum(ResultCode);
        _Serializer << DeleteCharNickName;

    }                                                           
                                                                
    void Deserialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        _Serializer.ReadEnum(ResultCode);
        _Serializer >> DeleteCharNickName;

    }                                                           
};                                                              

class SelectCharacterResultPacket : public ServerPacketBase                    
{                                                               
public:                                                         
	EResultCode ResultCode;
	EGameSession GameSessionType;
	std::string SelectCharNickName;
                                                                
public:                                                         
    SelectCharacterResultPacket()                                               
        : ServerPacketBase(PacketType::SelectCharacterResult)                    
        , ResultCode()
        , GameSessionType()
        , SelectCharNickName()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~SelectCharacterResultPacket() {}             
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(ResultCode) + DataSizeCheck(GameSessionType) + DataSizeCheck(SelectCharNickName);
    }                                                           
                                                                
    void Serialize(ServerSerializer& _Serializer)           
    {                                                           
        ServerPacketBase::Serialize(_Serializer);              
        _Serializer.WriteEnum(ResultCode);
        _Serializer.WriteEnum(GameSessionType);
        _Serializer << SelectCharNickName;

    }                                                           
                                                                
    void Deserialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        _Serializer.ReadEnum(ResultCode);
        _Serializer.ReadEnum(GameSessionType);
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

class UDPStartResultPacket : public ServerPacketBase                    
{                                                               
public:                                                         
	uint64_t PlayerID;
                                                                
public:                                                         
    UDPStartResultPacket()                                               
        : ServerPacketBase(PacketType::UDPStartResult)                    
        , PlayerID()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~UDPStartResultPacket() {}             
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(PlayerID);
    }                                                           
                                                                
    void Serialize(ServerSerializer& _Serializer)           
    {                                                           
        ServerPacketBase::Serialize(_Serializer);              
        _Serializer << PlayerID;

    }                                                           
                                                                
    void Deserialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        _Serializer >> PlayerID;

    }                                                           
};                                                              

class AllPlayerInfoPacket : public ServerPacketBase                    
{                                                               
public:                                                         
	std::vector<FPlayerUpdateData> AllPlayerInfo;
                                                                
public:                                                         
    AllPlayerInfoPacket()                                               
        : ServerPacketBase(PacketType::AllPlayerInfo)                    
        , AllPlayerInfo()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~AllPlayerInfoPacket() {}             
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(AllPlayerInfo);
    }                                                           
                                                                
    void Serialize(ServerSerializer& _Serializer)           
    {                                                           
        ServerPacketBase::Serialize(_Serializer);              
        _Serializer.WriteVector(AllPlayerInfo);

    }                                                           
                                                                
    void Deserialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        _Serializer.ReadVector(AllPlayerInfo);

    }                                                           
};                                                              

class SpawnOtherPlayerPacket : public ServerPacketBase                    
{                                                               
public:                                                         
	std::vector<FPlayerUpdateData> AllPlayerInfo;
                                                                
public:                                                         
    SpawnOtherPlayerPacket()                                               
        : ServerPacketBase(PacketType::SpawnOtherPlayer)                    
        , AllPlayerInfo()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~SpawnOtherPlayerPacket() {}             
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(AllPlayerInfo);
    }                                                           
                                                                
    void Serialize(ServerSerializer& _Serializer)           
    {                                                           
        ServerPacketBase::Serialize(_Serializer);              
        _Serializer.WriteVector(AllPlayerInfo);

    }                                                           
                                                                
    void Deserialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        _Serializer.ReadVector(AllPlayerInfo);

    }                                                           
};                                                              

class GameMatchPacket : public ServerPacketBase                    
{                                                               
public:                                                         
	int sessionIdx;
	int playerIdx;
	std::vector<FPlayerUpdateData> AllPlayerInfo;
                                                                
public:                                                         
    GameMatchPacket()                                               
        : ServerPacketBase(PacketType::GameMatch)                    
        , sessionIdx()
        , playerIdx()
        , AllPlayerInfo()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~GameMatchPacket() {}             
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(sessionIdx) + DataSizeCheck(playerIdx) + DataSizeCheck(AllPlayerInfo);
    }                                                           
                                                                
    void Serialize(ServerSerializer& _Serializer)           
    {                                                           
        ServerPacketBase::Serialize(_Serializer);              
        _Serializer << sessionIdx;
        _Serializer << playerIdx;
        _Serializer.WriteVector(AllPlayerInfo);

    }                                                           
                                                                
    void Deserialize(ServerSerializer& _Serializer)         
    {                                                           
        ServerPacketBase::Deserialize(_Serializer);            
        _Serializer >> sessionIdx;
        _Serializer >> playerIdx;
        _Serializer.ReadVector(AllPlayerInfo);

    }                                                           
};                                                              

