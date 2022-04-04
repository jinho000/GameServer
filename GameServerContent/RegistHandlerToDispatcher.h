#pragma once									
template<class Session>							
PacketDispatcher<Session>::PacketDispatcher()	
{												
	// dispatcher에 패킷을 처리할 함수 추가			
	AddHandler(PacketType::Login, std::bind(&ProcessHandler<LoginPacket, LoginPacketHandler>, std::placeholders::_1, std::placeholders::_2));	
	AddHandler(PacketType::Join, std::bind(&ProcessHandler<JoinPacket, JoinPacketHandler>, std::placeholders::_1, std::placeholders::_2));	
	AddHandler(PacketType::CreateCharacter, std::bind(&ProcessHandler<CreateCharacterPacket, CreateCharacterPacketHandler>, std::placeholders::_1, std::placeholders::_2));	
	AddHandler(PacketType::SelectCharacter, std::bind(&ProcessHandler<SelectCharacterPacket, SelectCharacterPacketHandler>, std::placeholders::_1, std::placeholders::_2));	
	AddHandler(PacketType::ChatMessage, std::bind(&ProcessHandler<ChatMessagePacket, ChatMessagePacketHandler>, std::placeholders::_1, std::placeholders::_2));	
}			
