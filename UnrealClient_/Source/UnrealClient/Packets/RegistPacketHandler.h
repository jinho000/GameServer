void UPacketComponent::RegistPacketHandler()							
{																		
	m_pGameInst = Cast<UCGameInstance>(GetOwner()->GetGameInstance());	
	UWorld* world = GetWorld();											
	m_handlerContainer.Add(PacketType::LoginResult, std::bind(&ProcessHandler<LoginResultPacketHandler, LoginResultPacket>, std::placeholders::_1, m_pGameInst, world));	
	m_handlerContainer.Add(PacketType::ChatMessage, std::bind(&ProcessHandler<ChatMessagePacketHandler, ChatMessagePacket>, std::placeholders::_1, m_pGameInst, world));	
}
