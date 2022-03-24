#include <iostream>
#include <GameServerBase/pch.h>
#include <GameServerBase/ServerDebug.h>
#include <GameServerBase/GameServerFile.h>
#include <GameServerBase/GameServerDirectory.h>
#include <GameServerBase/ServerString.h>

#pragma comment(lib, "GameServerBase.lib")

class MemberInfo
{
public:
	std::string MemberText;
	std::string Type;
	std::string Name;
};

class MessageInfo
{
public:
	std::string Name;
	std::vector<MemberInfo> Member;
};

struct CodeSave
{
	std::string savePath;
	std::string code;
};

void SerializerTypeCheck(std::string& _Text, MemberInfo& _MemberInfo)
{
	if (_MemberInfo.Type == "std::string")
	{
		_Text += "        _Serializer << " + _MemberInfo.Name + ";\n";
	}
	else if (_MemberInfo.Type == "int")
	{
		_Text += "        _Serializer << " + _MemberInfo.Name + ";\n";
	}
	else if (_MemberInfo.Type == "FVector")
	{
		_Text += "        _Serializer << " + _MemberInfo.Name + ";\n";
	}
	else
	{
		if (_MemberInfo.Type[0] == 'E')
		{
			_Text += "        _Serializer.WriteEnum(" + _MemberInfo.Name + ");\n";
		}
		else
		{
			ServerDebug::AssertDebugMsg("파악할수 없는 타입이 체크되었습니다. Name : " + _MemberInfo.Name + " Type : " + _MemberInfo.Type);
		}
	}
}

void DeSerializerTypeCheck(std::string& _Text, MemberInfo& _MemberInfo)
{
	if (_MemberInfo.Type == "std::string")
	{
		_Text += "        _Serializer >> " + _MemberInfo.Name + ";\n";
	}
	else if (_MemberInfo.Type == "int")
	{
		_Text += "        _Serializer >> " + _MemberInfo.Name + ";\n";
	}
	else if (_MemberInfo.Type == "FVector")
	{
		_Text += "        _Serializer >> " + _MemberInfo.Name + ";\n";
	}
	else
	{
		if (_MemberInfo.Type[0] == 'E')
		{
			_Text += "        _Serializer.ReadEnum(" + _MemberInfo.Name + ");\n";
		}
		else
		{
			ServerDebug::AssertDebugMsg("파악할수 없는 타입이 체크되었습니다. Name : " + _MemberInfo.Name + " Type : " + _MemberInfo.Type);
		}
	}
}

void MessageHeaderCreate(std::vector<MessageInfo>& _Collection, const std::string Path, std::vector<CodeSave>& _vecSave)
{
	std::string MessageText;

	MessageText += "#pragma once\n";
	MessageText += "#include \"ServerPacketBase.h\"\n";
	MessageText += "\n";


	for (size_t i = 0; i < _Collection.size(); i++)
	{
		MessageText += "class " + _Collection[i].Name + "Packet : public ServerPacketBase                    \n";
		MessageText += "{                                                               \n";
		MessageText += "public:                                                         \n";

		std::vector<MemberInfo>& MemberList = _Collection[i].Member;

		for (size_t m = 0; m < MemberList.size(); m++)
		{
			MessageText += "\t" + MemberList[m].MemberText + ";\n";
		}

		MessageText += "                                                                \n";
		MessageText += "public:                                                         \n";
		MessageText += "    " + _Collection[i].Name + "Packet()                                               \n";
		MessageText += "        : ServerPacketBase(PacketType::" + _Collection[i].Name + ")                    \n";
		for (size_t m = 0; m < MemberList.size(); m++)
		{
			MessageText += "        , " + MemberList[m].Name + "()\n";
		}
		MessageText += "    {                                                           \n";
		MessageText += "                                                                \n";
		MessageText += "    }                                                           \n";
		MessageText += "                                                                \n";
		MessageText += "    virtual ~" + _Collection[i].Name + "Packet() {}             \n";
		MessageText += "                                                                \n";
		MessageText += "    virtual int SizeCheck()                                     \n";
		MessageText += "    {                                                           \n";
		if (0 != MemberList.size())
		{
			MessageText += "\t\treturn ";

			for (size_t m = 0; m < MemberList.size(); m++)
			{
				MessageText += "DataSizeCheck(" + MemberList[m].Name + ")";
				MessageText += m != MemberList.size() - 1 ? " + " : ";\n";
			}
		}
		else
		{
			MessageText += "\t\treturn 0;";
		}
		MessageText += "    }                                                           \n";
		MessageText += "                                                                \n";
		MessageText += "    void Serialize(ServerSerializer& _Serializer)           \n";
		MessageText += "    {                                                           \n";
		MessageText += "        ServerPacketBase::Serialize(_Serializer);              \n";
		for (size_t m = 0; m < MemberList.size(); m++)
		{
			SerializerTypeCheck(MessageText, MemberList[m]);
		}
		MessageText += "\n";
		MessageText += "    }                                                           \n";
		MessageText += "                                                                \n";
		MessageText += "    void DeSerialize(ServerSerializer& _Serializer)         \n";
		MessageText += "    {                                                           \n";
		MessageText += "        ServerPacketBase::Deserialize(_Serializer);            \n";
		for (size_t m = 0; m < MemberList.size(); m++)
		{
			DeSerializerTypeCheck(MessageText, MemberList[m]);
		}
		MessageText += "\n";
		MessageText += "    }                                                           \n";
		MessageText += "};                                                              \n";
		MessageText += "\n";
	}

	_vecSave.push_back({ Path , MessageText });

}

void MessageReflection(std::vector<MessageInfo>& _Collection, const std::string& Code)
{
	std::vector<std::string> ClientMessageString = ServerString::split(Code, '|');
	for (size_t i = 0; i < ClientMessageString.size(); i++)
	{
		if (ClientMessageString[i] == "")
		{
			continue;
		}

		std::vector<std::string> MemberAndName = ServerString::split(ClientMessageString[i], '-');

		std::string& Name = MemberAndName[0];

		MessageInfo Info;
		Info.Name = Name;

		if (1 >= MemberAndName.size())
		{
			_Collection.push_back(Info);
			continue;
		}


		std::string& MmeberInfo = MemberAndName[1];


		std::vector<std::string> Members = ServerString::split(MmeberInfo, ';');

		for (size_t i = 0; i < Members.size(); i++)
		{
			MemberInfo NewInfo;

			NewInfo.MemberText = Members[i];

			ServerString::ClearText(NewInfo.MemberText);

			if (NewInfo.MemberText == "")
			{
				continue;
			}

			std::vector<std::string> TypeAndName = ServerString::split(NewInfo.MemberText, ' ');

			NewInfo.Type = TypeAndName[0];
			NewInfo.Name = TypeAndName[1];

			Info.Member.push_back(NewInfo);

		}

		_Collection.push_back(Info);
	}
}

int main()
{

	std::vector<MessageInfo> AllMessage;
	std::vector<MessageInfo> ClientMessage;
	std::vector<MessageInfo> ServerMessage;
	std::vector<MessageInfo> ServerClientMessage;
	std::vector<CodeSave>	 vecSaveFile;


	// 만들고 나면 다 단순복사가 됩니다 ok?
	{
		GameServerDirectory LoadDir;
		LoadDir.MoveParent("Project");
		LoadDir.MoveChild("GameServerPacket\\PacketInfo");
		{
			GameServerFile LoadFile = { LoadDir.PathToPlusFileName("ClientToServer.txt"), "rt" };
			std::string Code = LoadFile.GetString();

			MessageReflection(ClientMessage, Code);
			int a = 0;
		}

		{
			GameServerFile LoadFile = { LoadDir.PathToPlusFileName("ServerToClient.txt"), "rt" };
			std::string Code = LoadFile.GetString();

			MessageReflection(ServerMessage, Code);
			int a = 0;
		}

		{
			GameServerFile LoadFile = { LoadDir.PathToPlusFileName("ServerAndClient.txt"), "rt" };
			std::string Code = LoadFile.GetString();

			MessageReflection(ServerClientMessage, Code);
			int a = 0;
		}

		for (size_t i = 0; i < ClientMessage.size(); i++)
		{
			AllMessage.push_back(ClientMessage[i]);
		}
		for (size_t i = 0; i < ServerMessage.size(); i++)
		{
			AllMessage.emplace_back(ServerMessage[i]);
		}
		for (size_t i = 0; i < ServerClientMessage.size(); i++)
		{
			AllMessage.emplace_back(ServerClientMessage[i]);
		}


	}


	/////////////////////////////////// 서버 파일생성
	{

		///ENUMFILE CREATE////////////////////////////////////////////////////////////////////////////
		{
			GameServerDirectory FileDir;
			FileDir.MoveParent("Project");
			FileDir.MoveChild("GameServerPacket");

			std::string EnumFileText = "#pragma once\n\nenum class PacketType \n{\n";

			for (size_t i = 0; i < AllMessage.size(); i++)
			{
				EnumFileText += "\t" + AllMessage[i].Name + ",\n";
			}

			EnumFileText += "\t";
			EnumFileText += "MAX";
			EnumFileText += "\n";
			EnumFileText += "};";

			std::string SavePath = FileDir.PathToPlusFileName("PacketType.h");
			vecSaveFile.push_back({ SavePath, EnumFileText });
		}

		///CONVERT FILE CREATE////////////////////////////////////////////////////////////////////////////
		{
			GameServerDirectory FileDir;
			FileDir.MoveParent("Project");
			FileDir.MoveChild("GameServerPacket");

			std::string ConvertFileText = "#include \"pch.h\"\n";
			// header
			ConvertFileText += "#include \"PacketConvertor.h\"\n";
			ConvertFileText += "#include \"ServerSerializer.h\"\n";
			ConvertFileText += "#include \"Packets.h\"\n\n";

			ConvertFileText += "PacketConvertor::PacketConvertor(const std::vector<unsigned char>&_buffer)\n";
			ConvertFileText += "\t: m_packet(nullptr)\n";
			ConvertFileText += "{\n";
			ConvertFileText += "\tServerSerializer sr(_buffer);\n";
			ConvertFileText += "\n";
			ConvertFileText += "\tPacketType type;\n";
			ConvertFileText += "\tmemcpy_s(&type, sizeof(PacketType), _buffer.data(), sizeof(PacketType));\n";
			ConvertFileText += "\tswitch (type)\n\t{\n";

			for (size_t i = 0; i < AllMessage.size(); i++)
			{
				ConvertFileText += "\tcase PacketType::" + AllMessage[i].Name + ":\n";
				ConvertFileText += "\t\tm_packet = std::make_shared<" + AllMessage[i].Name + "Packet>();\n";
				ConvertFileText += "\t\tbreak;\n";
			}

			ConvertFileText += "\tdefault:\n";
			ConvertFileText += "\t\treturn;\n\t}\n\n";

			ConvertFileText += "\t*m_packet << sr;\n}\n";

			std::string SavePath = FileDir.PathToPlusFileName("PacketConvertor.cpp");

			vecSaveFile.push_back({ SavePath, ConvertFileText });
		}

		///Message Header////////////////////////////////////////////////////////////////////////////
		{
			GameServerDirectory FileDir;
			FileDir.MoveParent("Project");
			FileDir.MoveChild("GameServerPacket");

			MessageHeaderCreate(ClientMessage, FileDir.PathToPlusFileName("ClientToServer.h"), vecSaveFile);
			MessageHeaderCreate(ServerMessage, FileDir.PathToPlusFileName("ServerToClient.h"), vecSaveFile);
			MessageHeaderCreate(ServerClientMessage, FileDir.PathToPlusFileName("ServerAndClient.h"), vecSaveFile);

		}


		///DispatcherFile CREATE////////////////////////////////////////////////////////////////////////////
		{
			// Dispatcher 클래스 옮기기
			std::string Code;
			Code += "#pragma once									\n";
			Code += "template<class Session>							\n";
			Code += "PacketDispatcher<Session>::PacketDispatcher()	\n";
			Code += "{												\n";
			Code += "	// dispatcher에 패킷을 처리할 함수 추가			\n";
			for (size_t i = 0; i < ClientMessage.size(); i++)
			{
				Code += "	AddHandler(PacketType::" + ClientMessage[i].Name + ", std::bind(&ProcessHandler<" + ClientMessage[i].Name + "Packet, " + ClientMessage[i].Name + "PacketHandler>, std::placeholders::_1, std::placeholders::_2));	\n";
			}

			for (size_t i = 0; i < ServerClientMessage.size(); i++)
			{
				Code += "	AddHandler(PacketType::" + ServerClientMessage[i].Name + ", std::bind(&ProcessHandler<" + ServerClientMessage[i].Name + "Packet, " + ServerClientMessage[i].Name + "PacketHandler>, std::placeholders::_1, std::placeholders::_2));	\n";
			}
			Code += "}			\n";

			GameServerDirectory FileDir;
			FileDir.MoveParent("Project");
			FileDir.MoveChild("GameServerPacket");

			std::string SavePath = FileDir.PathToPlusFileName("RegistHandlerToDispatcher.h");
			vecSaveFile.push_back({ SavePath , Code });


		}

		// PacketHandlerHeader 
		{
			std::string Code;
			Code += "#pragma once									\n";

			for (size_t i = 0; i < ClientMessage.size(); i++)
			{
				Code += "#include \"" + ClientMessage[i].Name + "PacketHandler.h\"\n";
			}

			for (size_t i = 0; i < ServerClientMessage.size(); i++)
			{
				Code += "#include \"" + ServerClientMessage[i].Name + "PacketHandler.h\"\n";
			}

			GameServerDirectory FileDir;
			FileDir.MoveParent("Project");
			FileDir.MoveChild("GameServerPacket");

			std::string SavePath = FileDir.PathToPlusFileName("PacketHandlerHeader.h");
			vecSaveFile.push_back({ SavePath , Code });
		}

	}


	/////////////////////////////////////////////////////////////// 언리얼로 수정 파일 이동.
	{
		GameServerDirectory FileDir;
		FileDir.MoveParent("Project");
		FileDir.MoveChild("GameServerPacket");

		GameServerDirectory SaveDir;
		SaveDir.MoveParent("Project");
		SaveDir.MoveChild("UnrealClient_\\Source\\UnrealClient\\Packets");

		{
			GameServerFile LoadFile = { FileDir.PathToPlusFileName("ServerSerializer.h"), "rt" };
			std::string Code = LoadFile.GetString();

			std::string SavePath = SaveDir.PathToPlusFileName("ClientPackets\\ServerSerializer.h");
			
			vecSaveFile.push_back({ SavePath , Code});
		}

		{
			GameServerFile LoadFile = { FileDir.PathToPlusFileName("ServerSerializer.cpp"), "rt" };
			std::string Code = LoadFile.GetString();

			Code.erase(0, strlen("#include \"pch.h\"") + 1);
			std::string SavePath = SaveDir.PathToPlusFileName("ClientPackets\\ServerSerializer.cpp");
			vecSaveFile.push_back({ SavePath , Code });

		}

		{
			GameServerFile LoadFile = { FileDir.PathToPlusFileName("ServerPacketBase.h"), "rt" };
			std::string Code = LoadFile.GetString();

			std::string SavePath = SaveDir.PathToPlusFileName("ClientPackets\\ServerPacketBase.h");
			vecSaveFile.push_back({ SavePath , Code });
		}


		{
			GameServerFile LoadFile = { FileDir.PathToPlusFileName("ServerToClient.h"), "rt" };
			std::string Code = LoadFile.GetString();
			std::string SavePath = SaveDir.PathToPlusFileName("ClientPackets\\ServerToClient.h");
			vecSaveFile.push_back({ SavePath , Code });
		}

		{
			GameServerFile LoadFile = { FileDir.PathToPlusFileName("ClientToServer.h"), "rt" };
			std::string Code = LoadFile.GetString();
			std::string SavePath = SaveDir.PathToPlusFileName("ClientPackets\\ClientToServer.h");
			vecSaveFile.push_back({ SavePath , Code });
		}

		{
			GameServerFile LoadFile = { FileDir.PathToPlusFileName("ServerAndClient.h"), "rt" };
			std::string Code = LoadFile.GetString();
			std::string SavePath = SaveDir.PathToPlusFileName("ClientPackets\\ServerAndClient.h");
			vecSaveFile.push_back({ SavePath , Code });
		}


		{
			GameServerFile LoadFile = { FileDir.PathToPlusFileName("Packets.h"), "rt" };
			std::string Code = LoadFile.GetString();

			std::string SavePath = SaveDir.PathToPlusFileName("ClientPackets\\Packets.h");
			vecSaveFile.push_back({ SavePath , Code });
		}


		{
			GameServerFile LoadFile = { FileDir.PathToPlusFileName("PacketType.h"), "rt" };
			std::string Code = LoadFile.GetString();

			std::string SavePath = SaveDir.PathToPlusFileName("ClientPackets\\PacketType.h");
			vecSaveFile.push_back({ SavePath , Code });
		}

		{
			GameServerFile LoadFile = { FileDir.PathToPlusFileName("PacketConvertor.h"), "rt" };
			std::string Code = LoadFile.GetString();

			Code.replace(Code.find("#include \"ServerPacketBase.h\"\n")
				, strlen("#include \"ServerPacketBase.h\"\n")
				, "#include \"ClientPackets/ServerPacketBase.h\"\n");

			std::string SavePath = SaveDir.PathToPlusFileName("PacketConvertor.h");
			vecSaveFile.push_back({ SavePath , Code });

		}

		{
			GameServerFile LoadFile = { FileDir.PathToPlusFileName("PacketConvertor.cpp"), "rt" };
			std::string Code = LoadFile.GetString();

			Code.erase(0, strlen("#include \"pch.h\"") + 1);

			Code.replace(Code.find("#include \"ServerSerializer.h\"\n")
				, strlen("#include \"ServerSerializer.h\"\n")
				, "#include \"ClientPackets/ServerSerializer.h\"\n");

			Code.replace(Code.find("#include \"Packets.h\"\n")
				, strlen("#include \"Packets.h\"\n")
				, "#include \"ClientPackets/Packets.h\"\n");

			std::string SavePath = SaveDir.PathToPlusFileName("PacketConvertor.cpp");
			vecSaveFile.push_back({ SavePath , Code });

		}

		{
			std::string Code;
			Code += "#pragma once									\n";

			for (size_t i = 0; i < ServerMessage.size(); i++)
			{
				Code += "#include \"" + ServerMessage[i].Name + "PacketHandler.h\"\n";
			}

			for (size_t i = 0; i < ServerClientMessage.size(); i++)
			{
				Code += "#include \"" + ServerClientMessage[i].Name + "PacketHandler.h\"\n";
			}

			std::string SavePath = SaveDir.PathToPlusFileName("PacketHandler\\PacketHandlerHeader.h");
			vecSaveFile.push_back({ SavePath , Code });
		}

		{
			/// Regist Packet Handelr ////////////////////////////////////////////////////////////////////////////
			std::string Code;

			Code += "void UPacketComponent::RegistPacketHandler()							\n";		
			Code += "{																		\n";

			Code += "	m_pGameInst = Cast<UCGameInstance>(GetOwner()->GetGameInstance());	\n";
			Code += "	UWorld* world = GetWorld();											\n";

			for (size_t i = 0; i < ServerMessage.size(); i++)
			{
				Code += "	m_handlerContainer.Add(PacketType::" + ServerMessage[i].Name
					+ ", std::bind(&ProcessHandler<" + ServerMessage[i].Name + "PacketHandler, "
					+ ServerMessage[i].Name + "Packet>, std::placeholders::_1, m_pGameInst, world));	\n";
			}

			for (size_t i = 0; i < ServerClientMessage.size(); i++)
			{
				Code += "	m_handlerContainer.Add(PacketType::" + ServerClientMessage[i].Name
					+ ", std::bind(&ProcessHandler<" + ServerClientMessage[i].Name + "PacketHandler, "
					+ ServerClientMessage[i].Name + "Packet>, std::placeholders::_1, m_pGameInst, world));	\n";
			}

			Code += "}\n";

			std::string SavePath = SaveDir.PathToPlusFileName("RegistPacketHandler.h");
			vecSaveFile.push_back({ SavePath , Code });
			
		}
	}

	for (size_t i = 0; i < vecSaveFile.size(); i++)
	{
		GameServerFile SaveFile = GameServerFile{ vecSaveFile[i].savePath, "wt"};
		SaveFile.Write(vecSaveFile[i].code.c_str(), vecSaveFile[i].code.size());
	}

	return 0;
}
