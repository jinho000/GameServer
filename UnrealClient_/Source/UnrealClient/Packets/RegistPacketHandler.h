void UPacketComponent::RegistPacketHandler()							
{																		
	m_pGameInst = Cast<UCGameInstance>(GetOwner()->GetGameInstance());	
	UWorld* world = GetWorld();											
	m_handlerContainer.insert(std::make_pair(PacketType::LoginResult, std::bind(&ProcessHandler<LoginResultPacketHandler, LoginResultPacket>, std::placeholders::_1, m_pGameInst, world)));	
	m_handlerContainer.insert(std::make_pair(PacketType::JoginResult, std::bind(&ProcessHandler<JoginResultPacketHandler, JoginResultPacket>, std::placeholders::_1, m_pGameInst, world)));	
	m_handlerContainer.insert(std::make_pair(PacketType::CharacterList, std::bind(&ProcessHandler<CharacterListPacketHandler, CharacterListPacket>, std::placeholders::_1, m_pGameInst, world)));	
	m_handlerContainer.insert(std::make_pair(PacketType::CreateCharacterResult, std::bind(&ProcessHandler<CreateCharacterResultPacketHandler, CreateCharacterResultPacket>, std::placeholders::_1, m_pGameInst, world)));	
	m_handlerContainer.insert(std::make_pair(PacketType::DeleteCharacterResult, std::bind(&ProcessHandler<DeleteCharacterResultPacketHandler, DeleteCharacterResultPacket>, std::placeholders::_1, m_pGameInst, world)));	
	m_handlerContainer.insert(std::make_pair(PacketType::SelectCharacterResult, std::bind(&ProcessHandler<SelectCharacterResultPacketHandler, SelectCharacterResultPacket>, std::placeholders::_1, m_pGameInst, world)));	
	m_handlerContainer.insert(std::make_pair(PacketType::InsertSectionResult, std::bind(&ProcessHandler<InsertSectionResultPacketHandler, InsertSectionResultPacket>, std::placeholders::_1, m_pGameInst, world)));	
	m_handlerContainer.insert(std::make_pair(PacketType::UDPStartResult, std::bind(&ProcessHandler<UDPStartResultPacketHandler, UDPStartResultPacket>, std::placeholders::_1, m_pGameInst, world)));	
	m_handlerContainer.insert(std::make_pair(PacketType::AllPlayerInfo, std::bind(&ProcessHandler<AllPlayerInfoPacketHandler, AllPlayerInfoPacket>, std::placeholders::_1, m_pGameInst, world)));	
	m_handlerContainer.insert(std::make_pair(PacketType::SpawnOtherPlayer, std::bind(&ProcessHandler<SpawnOtherPlayerPacketHandler, SpawnOtherPlayerPacket>, std::placeholders::_1, m_pGameInst, world)));	
	m_handlerContainer.insert(std::make_pair(PacketType::GameMatch, std::bind(&ProcessHandler<GameMatchPacketHandler, GameMatchPacket>, std::placeholders::_1, m_pGameInst, world)));	
	m_handlerContainer.insert(std::make_pair(PacketType::ChatMessage, std::bind(&ProcessHandler<ChatMessagePacketHandler, ChatMessagePacket>, std::placeholders::_1, m_pGameInst, world)));	
}
