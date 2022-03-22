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

void MessageHeaderCreate(std::vector<MessageInfo>& _Collection, const std::string Path)
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

	GameServerFile SaveFile = GameServerFile{ Path, "wt" };
	SaveFile.Write(MessageText.c_str(), MessageText.size());
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
	//COORD pos = { 0, 0 };

	//HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//SetConsoleCursorPosition(stdHandle, pos);

	std::vector<MessageInfo> AllMessage;
	std::vector<MessageInfo> ClientMessage;
	std::vector<MessageInfo> ServerMessage;
	std::vector<MessageInfo> ServerClientMessage;


	// 만들고 나면 다 단순복사가 됩니다 ok?
	{
		GameServerDirectory LoadDir;
		LoadDir.MoveParent("Project");
		LoadDir.MoveChild("GameServerNet\\PacketInfo");
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
			FileDir.MoveChild("GameServerNet");

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
			GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
			SaveFile.Write(EnumFileText.c_str(), EnumFileText.size());
			///////////////////////////////////////////////////////////////////////////////
		}

		///CONVERT FILE CREATE////////////////////////////////////////////////////////////////////////////
		{
			GameServerDirectory FileDir;
			FileDir.MoveParent("Project");
			FileDir.MoveChild("GameServerNet");

			std::string ConvertFileText = "#include \"pch.h\"\n";
			// header
			ConvertFileText += "#include \"PacketConvertor.h\"\n";
			ConvertFileText += "#include \"ServerSerializer.h\"\n";
			ConvertFileText += "#include \"ServerAndClient.h\"\n";
			ConvertFileText += "#include \"ServerToClient.h\"\n";
			ConvertFileText += "#include \"ClientToServer.h\"\n\n";

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
			ConvertFileText += "\t\tassert(nullptr);\n";
			ConvertFileText += "\t\treturn;\n\t}\n\n"; 
								
			ConvertFileText += "\t*m_packet << sr;\n}\n";

			std::string SavePath = FileDir.PathToPlusFileName("PacketConvertor.cpp");
			GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
			SaveFile.Write(ConvertFileText.c_str(), ConvertFileText.size());
		}
		
		///Message Header////////////////////////////////////////////////////////////////////////////
		{
			GameServerDirectory FileDir;
			FileDir.MoveParent("Project");
			FileDir.MoveChild("GameServerNet");

			MessageHeaderCreate(ClientMessage, FileDir.PathToPlusFileName("ClientToServer.h"));
			MessageHeaderCreate(ServerMessage, FileDir.PathToPlusFileName("ServerToClient.h"));
			MessageHeaderCreate(ServerClientMessage, FileDir.PathToPlusFileName("ServerAndClient.h"));

		}

		
		///DispatcherFile CREATE////////////////////////////////////////////////////////////////////////////
		{
			// Dispatcher 클래스 옮기기
			std::string DisText;
			DisText += "#pragma once									\n";
			DisText += "template<class Session>							\n";
			DisText += "PacketDispatcher<Session>::PacketDispatcher()	\n";
			DisText += "{												\n";
			DisText += "	// dispatcher에 패킷을 처리할 함수 추가			\n";
			for (size_t i = 0; i < ClientMessage.size(); i++)
			{
				DisText += "	AddHandler(PacketType::" + ClientMessage[i].Name + ", std::bind(&ProcessHandler<" + ClientMessage[i].Name + "Packet, " + ClientMessage[i].Name + "PacketHandler>, std::placeholders::_1, std::placeholders::_2));	\n";
			}

			for (size_t i = 0; i < ServerClientMessage.size(); i++)
			{
				DisText += "	AddHandler(PacketType::" + ServerClientMessage[i].Name + ", std::bind(&ProcessHandler<" + ServerClientMessage[i].Name + "Packet, " + ServerClientMessage[i].Name + "PacketHandler>, std::placeholders::_1, std::placeholders::_2));	\n";
			}
			DisText += "}			\n";
																																					
			GameServerDirectory FileDir;
			FileDir.MoveParent("Project");
			FileDir.MoveChild("GameServerNet");

			std::string SavePath = FileDir.PathToPlusFileName("RegistHandlerToDispatcher.h");
			GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
			SaveFile.Write(DisText.c_str(), DisText.size());

			
		}

		// PacketHandlerHeader 
		{
			std::string handlerHeaderTxt;
			handlerHeaderTxt += "#pragma once									\n";

			for (size_t i = 0; i < ClientMessage.size(); i++)
			{
				handlerHeaderTxt += "#include \"" + ClientMessage[i].Name + "PacketHandler.h\"\n";
			}

			for (size_t i = 0; i < ServerClientMessage.size(); i++)
			{
				handlerHeaderTxt += "#include \"" + ServerClientMessage[i].Name + "PacketHandler.h\"\n";
			}

			GameServerDirectory FileDir;
			FileDir.MoveParent("Project");
			FileDir.MoveChild("GameServerNet");

			std::string SavePath = FileDir.PathToPlusFileName("PacketHandlerHeader.h");
			GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
			SaveFile.Write(handlerHeaderTxt.c_str(), handlerHeaderTxt.size());
		}

		std::cout << "complete" << std::endl;
		return 0;
	}


	/////////////////////////////////////////////////////////////// 언리얼로 수정 파일 이동.
	{
		GameServerDirectory FileDir;
		FileDir.MoveParent();
		FileDir.MoveChild("GameServerBase");

		GameServerDirectory SaveDir;
		SaveDir.MoveParent();
		SaveDir.MoveParent();
		SaveDir.MoveChild("UnrealClient\\Source\\UnrealClient\\Message");


		{
			GameServerFile LoadFile = { FileDir.PathToPlusFileName("GameServerSerializer.h"), "rt" };
			std::string Code = LoadFile.GetString();

			Code.replace(Code.find("#include \"GameServerMathStruct.h\"\n")
				, strlen("#include \"GameServerMathStruct.h\"\n"), "\n");

			std::string SavePath = SaveDir.PathToPlusFileName("GameServerSerializer.h");
			GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
			SaveFile.Write(Code.c_str(), Code.size());
		}

		{
			GameServerFile LoadFile = { FileDir.PathToPlusFileName("GameServerSerializer.cpp"), "rt" };
			std::string Code = LoadFile.GetString();

			Code.erase(0, strlen("#include \"PreCompile.h\"") + 1);
			std::string SavePath = SaveDir.PathToPlusFileName("GameServerSerializer.cpp");
			GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
			SaveFile.Write(Code.c_str(), Code.size());
		}
	}


	{
		GameServerDirectory FileDir;
		FileDir.MoveParent();
		FileDir.MoveChild("GameServerMessage");

		GameServerDirectory SaveDir;
		SaveDir.MoveParent();
		SaveDir.MoveParent();
		SaveDir.MoveChild("UnrealClient\\Source\\UnrealClient\\Message");


		{
			GameServerFile LoadFile = { FileDir.PathToPlusFileName("GameServerMessage.h"), "rt" };
			std::string Code = LoadFile.GetString();

			Code.replace(Code.find("#include <GameServerBase/GameServerMathStruct.h>\n")
				, strlen("#include <GameServerBase/GameServerMathStruct.h>\n"), "\n");

			Code.replace(Code.find("#include <GameServerBase/GameServerSerializer.h>\n")
				, strlen("#include <GameServerBase/GameServerSerializer.h>\n"), "#include \"GameServerSerializer.h\"\n");

			std::string SavePath = SaveDir.PathToPlusFileName("GameServerMessage.h");
			GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
			SaveFile.Write(Code.c_str(), Code.size());
		}


		{
			GameServerFile LoadFile = { FileDir.PathToPlusFileName("ServerToClient.h"), "rt" };
			std::string Code = LoadFile.GetString();
			std::string SavePath = SaveDir.PathToPlusFileName("ServerToClient.h");
			GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
			SaveFile.Write(Code.c_str(), Code.size());
		}


		{
			GameServerFile LoadFile = { FileDir.PathToPlusFileName("ClientToServer.h"), "rt" };
			std::string Code = LoadFile.GetString();
			std::string SavePath = SaveDir.PathToPlusFileName("ClientToServer.h");
			GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
			SaveFile.Write(Code.c_str(), Code.size());
		}


		{
			GameServerFile LoadFile = { FileDir.PathToPlusFileName("ServerAndClient.h"), "rt" };
			std::string Code = LoadFile.GetString();
			std::string SavePath = SaveDir.PathToPlusFileName("ServerAndClient.h");
			GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
			SaveFile.Write(Code.c_str(), Code.size());
		}


		{
			GameServerFile LoadFile = { FileDir.PathToPlusFileName("Messages.h"), "rt" };
			std::string Code = LoadFile.GetString();


			//Code.replace(Code.find("#include <GameServerBase/GameServerSerializer.h>\n")
			//    , strlen("#include <GameServerBase/GameServerSerializer.h>\n"), "#include \"GameServerSerializer.h\"\n");


			std::string SavePath = SaveDir.PathToPlusFileName("Messages.h");
			GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
			SaveFile.Write(Code.c_str(), Code.size());
		}



		{
			GameServerFile LoadFile = { FileDir.PathToPlusFileName("MessageIdEnum.h"), "rt" };
			std::string Code = LoadFile.GetString();

			std::string SavePath = SaveDir.PathToPlusFileName("MessageIdEnum.h");
			GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
			SaveFile.Write(Code.c_str(), Code.size());
		}



		{
			GameServerFile LoadFile = { FileDir.PathToPlusFileName("MessageConverter.h"), "rt" };
			std::string Code = LoadFile.GetString();

			std::string SavePath = SaveDir.PathToPlusFileName("MessageConverter.h");
			GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
			SaveFile.Write(Code.c_str(), Code.size());
		}

		{
			GameServerFile LoadFile = { FileDir.PathToPlusFileName("MessageConverter.cpp"), "rt" };
			std::string Code = LoadFile.GetString();

			Code.erase(0, strlen("#include \"PreCompile.h\"") + 1);

			std::string SavePath = SaveDir.PathToPlusFileName("MessageConverter.cpp");
			GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
			SaveFile.Write(Code.c_str(), Code.size());
		}

		{
			///DisFile CREATE////////////////////////////////////////////////////////////////////////////
			std::string DisText;

			DisText += "#pragma once																									  \n";
			DisText += "#include \"CoreMinimal.h\"																						  \n";
			DisText += "#include <functional>																							 \n";
			DisText += "																												  \n";
			for (size_t i = 0; i < ServerMessage.size(); i++)
			{
				DisText += "#include \"ThreadHandler" + ServerMessage[i].Name + "Message.h\"\n";
			}

			for (size_t i = 0; i < ServerClientMessage.size(); i++)
			{
				DisText += "#include \"ThreadHandler" + ServerClientMessage[i].Name + "Message.h\"\n";
			}
			DisText += "																												  \n";
			DisText += "template<typename MessageHandler, typename MessageType>															  \n";
			DisText += "void OnMessageProcess(std::shared_ptr<GameServerMessage> _Message, UClientGameInstance* _Inst, UWorld* _World)	  \n";
			DisText += "{																												  \n";
			DisText += "	std::shared_ptr<MessageType> ConvertMessage = std::static_pointer_cast<MessageType>(_Message);				  \n";
			DisText += "	if (nullptr == ConvertMessage)																				  \n";
			DisText += "	{																											  \n";
			DisText += "		return;																									  \n";
			DisText += "	}																											  \n";
			DisText += "																												  \n";
			DisText += "	MessageHandler Cmd = MessageHandler(ConvertMessage);														  \n";
			DisText += "	Cmd.Init(_Inst, _World);																					  \n";
			DisText += "	Cmd.Start();																								  \n";
			DisText += "}																												  \n";
			DisText += "																												  \n";
			DisText += "void CheckHandler(Dispatcher& Dis, class UClientGameInstance* Inst, UWorld* World)								  \n";
			DisText += "{														\n";
			for (size_t i = 0; i < ServerMessage.size(); i++)
			{
				DisText += "	Dis.AddHandler(MessageId::" + ServerMessage[i].Name + ", std::bind(&OnMessageProcess<ThreadHandler" + ServerMessage[i].Name + "Message, " + ServerMessage[i].Name + "Message>, std::placeholders::_1, Inst, World));	\n";
			}

			for (size_t i = 0; i < ServerClientMessage.size(); i++)
			{
				DisText += "	Dis.AddHandler(MessageId::" + ServerClientMessage[i].Name + ", std::bind(&OnMessageProcess<ThreadHandler" + ServerClientMessage[i].Name + "Message, " + ServerClientMessage[i].Name + "Message>, std::placeholders::_1, Inst, World));	\n";
			}
			DisText += "}																																													\n";

			std::string SavePath = SaveDir.PathToPlusFileName("Handler\\HandlerHeader.h");
			GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
			SaveFile.Write(DisText.c_str(), DisText.size());
		}
	}

	//if (어떠한 사소한 문제라도 있었다면)
	//{
	//	return 1;
	//}
	// 

	return 0;
}
