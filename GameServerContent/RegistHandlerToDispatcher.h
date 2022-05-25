#pragma once									
template<class Session>							
PacketDispatcher<Session>::PacketDispatcher()	
{												
	// dispatcher에 패킷을 처리할 함수 추가			
	AddHandler(PacketType::Login, std::bind(&ProcessHandler<LoginPacket, LoginPacketHandler>, std::placeholders::_1, std::placeholders::_2));	
	AddHandler(PacketType::Join, std::bind(&ProcessHandler<JoinPacket, JoinPacketHandler>, std::placeholders::_1, std::placeholders::_2));	
	AddHandler(PacketType::CreateCharacter, std::bind(&ProcessHandler<CreateCharacterPacket, CreateCharacterPacketHandler>, std::placeholders::_1, std::placeholders::_2));	
	AddHandler(PacketType::SelectCharacter, std::bind(&ProcessHandler<SelectCharacterPacket, SelectCharacterPacketHandler>, std::placeholders::_1, std::placeholders::_2));	
	AddHandler(PacketType::DeleteCharacter, std::bind(&ProcessHandler<DeleteCharacterPacket, DeleteCharacterPacketHandler>, std::placeholders::_1, std::placeholders::_2));	
	AddHandler(PacketType::UDPStart, std::bind(&ProcessHandler<UDPStartPacket, UDPStartPacketHandler>, std::placeholders::_1, std::placeholders::_2));	
	AddHandler(PacketType::PlayerUpdate, std::bind(&ProcessHandler<PlayerUpdatePacket, PlayerUpdatePacketHandler>, std::placeholders::_1, std::placeholders::_2));	
	AddHandler(PacketType::RequestMath, std::bind(&ProcessHandler<RequestMathPacket, RequestMathPacketHandler>, std::placeholders::_1, std::placeholders::_2));	
	AddHandler(PacketType::ChatMessage, std::bind(&ProcessHandler<ChatMessagePacket, ChatMessagePacketHandler>, std::placeholders::_1, std::placeholders::_2));	
}			
