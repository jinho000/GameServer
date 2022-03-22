#pragma once									
template<class Session>							
PacketDispatcher<Session>::PacketDispatcher()	
{												
	// dispatcher에 패킷을 처리할 함수 추가			
	AddHandler(PacketType::Login, std::bind(&ProcessHandler<LoginPacket, LoginPacketHandler>, std::placeholders::_1, std::placeholders::_2));	
	AddHandler(PacketType::ChatMessage, std::bind(&ProcessHandler<ChatMessagePacket, ChatMessagePacketHandler>, std::placeholders::_1, std::placeholders::_2));	
}			
