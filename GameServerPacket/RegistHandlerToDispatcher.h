#pragma once									
template<class Session>							
PacketDispatcher<Session>::PacketDispatcher()	
{												
	// dispatcher�� ��Ŷ�� ó���� �Լ� �߰�			
	AddHandler(PacketType::Login, std::bind(&ProcessHandler<LoginPacket, LoginPacketHandler>, std::placeholders::_1, std::placeholders::_2));	
	AddHandler(PacketType::ChatMessage, std::bind(&ProcessHandler<ChatMessagePacket, ChatMessagePacketHandler>, std::placeholders::_1, std::placeholders::_2));	
}			
