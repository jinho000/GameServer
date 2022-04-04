void UPacketComponent::RegistPacketHandler()							
{																		
	m_pGameInst = Cast<UCGameInstance>(GetOwner()->GetGameInstance());	
	UWorld* world = GetWorld();											
	m_handlerContainer.insert(std::make_pair(PacketType::LoginResult, std::bind(&ProcessHandler<LoginResultPacketHandler, LoginResultPacket>, std::placeholders::_1, m_pGameInst, world)));	
	m_handlerContainer.insert(std::make_pair(PacketType::JoginResult, std::bind(&ProcessHandler<JoginResultPacketHandler, JoginResultPacket>, std::placeholders::_1, m_pGameInst, world)));	
	m_handlerContainer.insert(std::make_pair(PacketType::CharacterList, std::bind(&ProcessHandler<CharacterListPacketHandler, CharacterListPacket>, std::placeholders::_1, m_pGameInst, world)));	
	m_handlerContainer.insert(std::make_pair(PacketType::CreateCharacterResult, std::bind(&ProcessHandler<CreateCharacterResultPacketHandler, CreateCharacterResultPacket>, std::placeholders::_1, m_pGameInst, world)));	
	m_handlerContainer.insert(std::make_pair(PacketType::SelectCharacterResult, std::bind(&ProcessHandler<SelectCharacterResultPacketHandler, SelectCharacterResultPacket>, std::placeholders::_1, m_pGameInst, world)));	
	m_handlerContainer.insert(std::make_pair(PacketType::InsertSectionResult, std::bind(&ProcessHandler<InsertSectionResultPacketHandler, InsertSectionResultPacket>, std::placeholders::_1, m_pGameInst, world)));	
	m_handlerContainer.insert(std::make_pair(PacketType::ChatMessage, std::bind(&ProcessHandler<ChatMessagePacketHandler, ChatMessagePacket>, std::placeholders::_1, m_pGameInst, world)));	
}
